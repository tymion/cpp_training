#include <string>
#include <cstring>
#include <iostream>
#include <ctime>
#include "loader.h"
#include "region_coordinates.h"
#include "similar_region_search.h"

SimilarRegionSearch::SimilarRegionSearch(std::shared_ptr<IImage>& lImage, std::shared_ptr<IImage>& rImage)
{
    if (lImage->getHeight() != rImage->getHeight() || lImage->getWidth() != rImage->getWidth()) {
        throw std::invalid_argument("Images should have same sizes.");
    }
    _height = lImage->getHeight();
    _width = lImage->getWidth();
    _lbuffer = std::shared_ptr<RegionFactory>(new RegionFactory(lImage));
    _rbuffer = std::shared_ptr<RegionFactory>(new RegionFactory(rImage));
}

SimilarRegionSearch::SimilarRegionSearch(std::string lname, std::string rname)
{
    std::shared_ptr<IImage> lImage(Loader::loadImage(lname));
    std::shared_ptr<IImage> rImage(Loader::loadImage(rname));
    if (lImage->getHeight() != rImage->getHeight() || lImage->getWidth() != rImage->getWidth()) {
        throw std::invalid_argument("Images should have same sizes.");
    }
    _height = lImage->getHeight();
    _width = lImage->getWidth();
    _lbuffer = std::shared_ptr<RegionFactory>(new RegionFactory(lImage));
    _rbuffer = std::shared_ptr<RegionFactory>(new RegionFactory(rImage));
}

void SimilarRegionSearch::search_common(uint32_t rsize, std::unique_ptr<RegionBase>& lregion,
                                        std::unique_ptr<RegionBase>& rregion, RegionMap& map)
{
    double similar = 0;
    RegionCoordinates *coordinates = NULL;
    RegionMatchedList *list = NULL;
    RegionMatched *matched = NULL;
    bool test = false;
    for (uint32_t row = 0; row < _height - rsize; row++) {
        for (uint32_t col = 0; col < _width - rsize; col++) {
            _rbuffer->updateRegion(row, col, rregion);
            uint32_t s_row = (int32_t) row - 3 < 0 ? 0 : (int32_t) row - 3;
            uint32_t s_row_max = row + 3 > _height - rsize ? _height - rsize : row + 3;
            for (; s_row < s_row_max; s_row++) {
                for (uint32_t s_col = col; s_col < _width - rsize; s_col++) {
                    _lbuffer->updateRegion(s_row, s_col, lregion);
                    test = rregion->compare(*lregion, similar);
                    std::cout << "SubStep3:" << similar << std::endl;
                    if (test) {
                        std::cout << "SubStep3:" << similar << std::endl;
                        if (!coordinates) {
                            coordinates = (RegionCoordinates*) malloc(RegionCoordinatesSize);
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
                    }
                }
            }
            coordinates = NULL;
        }
        std::cout << "SubStep4:" << row << std::endl;
    }
    std::cout << "SubStep4=====:" << map.size() << std::endl;
}

void SimilarRegionSearch::search(uint8_t rsize, uint32_t similarity,
                                    double jacardThreshold, RegionMap& map)
{
    Configuration::setSimilarityThreshold(similarity);
    Configuration::setJacardThreshold(jacardThreshold);
    std::unique_ptr<RegionBase> rregion(_rbuffer->createRegion(rsize, rsize));
    std::unique_ptr<RegionBase> lregion(_lbuffer->createRegion(rsize, rsize));
    SimilarRegionSearch::search_common(rsize, lregion, rregion, map);
}

void SimilarRegionSearch::search(uint8_t rsize, uint32_t similarity,
                                    double jacardThreshold, std::shared_ptr<Mask> const& mask,
                                    RegionMap& map)
{
    Configuration::setSimilarityThreshold(similarity);
    Configuration::setJacardThreshold(jacardThreshold);
    std::unique_ptr<RegionBase> rregion(_rbuffer->createRegion(rsize, rsize));
    std::unique_ptr<RegionBase> lregion(_lbuffer->createRegion(rsize, rsize));
    rregion->setMask(mask);
    lregion->setMask(mask);
    SimilarRegionSearch::search_common(rsize, lregion, rregion, map);
}