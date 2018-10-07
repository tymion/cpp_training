#include <string>
#include <cstring>
#include <iostream>
#include <memory>
#include <ctime>
#include "region.h"
#include "loader.h"
#include "region_factory.h"
#include "region_coordinates.h"
#include "similar_region_search.h"

using namespace std;

SimilarRegionSearch::SimilarRegionSearch(string lname, string rname)
{
    shared_ptr<IImage> lImage = shared_ptr<IImage>(Loader::loadImage(lname));
    shared_ptr<IImage> rImage = shared_ptr<IImage>(Loader::loadImage(rname));
    if (lImage->getHeight() != rImage->getHeight() || lImage->getWidth() != rImage->getWidth()) {
        throw std::invalid_argument("Images should have same sizes.");
    }
    _height = lImage->getHeight();
    _width = lImage->getWidth();
    _lbuffer = shared_ptr<RegionFactory>(new RegionFactory(lImage));
    _rbuffer = shared_ptr<RegionFactory>(new RegionFactory(rImage));
}

void SimilarRegionSearch::search(uint8_t rsize, uint32_t similarity,
                                    double jacardThreshold, shared_ptr<Mask> &mask)
{
    Configuration::setSimilarityThreshold(similarity);
    Configuration::setJacardThreshold(jacardThreshold);
    unique_ptr<RegionBase> rregion = unique_ptr<RegionBase>(_rbuffer->createRegion(rsize, rsize));
    unique_ptr<RegionBase> lregion = unique_ptr<RegionBase>(_lbuffer->createRegion(rsize, rsize));
    if (mask != nullptr) {
        rregion->setMask(mask);
        lregion->setMask(mask);
    }
    double similar = 0;
    uint32_t cnt = 0;
    RegionMap map;
    RegionCoordinates coordinates = NULL;
    RegionMatchedList *list = NULL;
    RegionMatched *matched = NULL;
    clock_t start = clock();
    for (uint32_t row = 0; row < height - rsize; row++) {
        for (uint32_t col = 0; col < width - rsize; col++) {
            _rbuffer->updateRegion(row, col, rregion);
            uint32_t s_row = (int32_t) row - 3 < 0 ? 0 : (int32_t) row - 3;
            uint32_t s_row_max = row + 3 > height - rsize ? height - rsize : row + 3;
            for (; s_row < s_row_max; s_row++) {
                for (uint32_t s_col = col; s_col < width - rsize; s_col++) {
                    _lbuffer->updateRegion(s_row, s_col, lregion);
                    if (rregion->compare(*lregion, similar)) {
                        if (!coordinates) {
                            coordinates = (RegionCoordinates) malloc(RegionCoordinatesSize);
                            coordinates->row = row;
                            coordinates->col = col;
                            list = new RegionMatchedList();
                            map[coordinates] = list;
                        }
                        matched = new RegionMatched();
                        matched->coordinates.row = s_row;
                        matched->coordinates.col = s_col;
                        matched->similarity_degree = similar;
                        list->push_back(matched);
                        cnt++;
                    }
                }
            }
            coordinates = NULL;
        }
        cout << "SubStep4:" << row << endl;
    }
    double duration = (clock() - start) / (double) CLOCKS_PER_SEC;
    cout << "Time: "<< duration << endl;
    cout << "Cout:" << cnt << endl;
    cout << "Coordinates:" << map.size() << endl;
}
