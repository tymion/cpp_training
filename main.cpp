#include <string>
#include <cstring>
#include <exception>
#include <iostream>
#include <memory>
#include <ctime>
#include "region.h"
#include "loader.h"
#include "region_factory.h"
#include "region_coordinates.h"

using namespace std;

#define rsize 7

int main() {
    std::clock_t start;
    double duration;
    string leftFile = "resources/left.png";
    //string rightFile = "resources/left.png";
    string rightFile = "resources/right.png";
    try {
        std::shared_ptr<IImage> lImage = std::shared_ptr<IImage>(Loader::loadImage(leftFile));
        std::shared_ptr<IImage> rImage = std::shared_ptr<IImage>(Loader::loadImage(rightFile));
        uint32_t height = lImage->getHeight();
        uint32_t width = lImage->getWidth();
        std::unique_ptr<RegionFactory> lbuffer = std::unique_ptr<RegionFactory>(new RegionFactory(lImage));
        std::unique_ptr<RegionFactory> rbuffer = std::unique_ptr<RegionFactory>(new RegionFactory(rImage));
        uint8_t maskData[rsize*rsize];
        std::memset(maskData, 1, sizeof(maskData));
        std::shared_ptr<Mask> mask = std::shared_ptr<Mask>(new Mask(rsize, rsize, maskData));
        RegionBase *rregion = rbuffer->createRegion(rsize, rsize);
        RegionBase *lregion = lbuffer->createRegion(rsize, rsize);
        rregion->setMask(mask);
        lregion->setMask(mask);
        double similarity = 0;
        uint32_t cnt = 0;
        Configuration::setSimilarityThreshold(1);
        Configuration::setJacardThreshold(0.5);
        RegionMap map;
        RegionCoordinates coordinates = NULL;
        RegionMatchedList *list = NULL;
        RegionMatched *matched = NULL;
        start = std::clock();
        for (uint32_t row = 0; row < height - rsize; row++) {
            for (uint32_t col = 0; col < width - rsize; col++) {
                rbuffer->updateRegion(row, col, rregion);
                uint32_t s_row = (int32_t) row - 3 < 0 ? 0 : (int32_t) row - 3;
                uint32_t s_row_max = row + 3 > height - rsize ? height - rsize : row + 3;
                for (; s_row < s_row_max; s_row++) {
                    for (uint32_t s_col = col; s_col < width - rsize; s_col++) {
                        lbuffer->updateRegion(s_row, s_col, lregion);
                        if (rregion->compare(*lregion, similarity)) {
//                        if (*rregion == *lregion) {
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
                            matched->similarity_degree = similarity;
                            list->push_back(matched);
                            cnt++;
                        }
                    }
                }
                coordinates = NULL;
            }
            std::cout << "SubStep4:" << row << std::endl;
        }
        duration = (std::clock() - start) / (double) CLOCKS_PER_SEC;
        std::cout << "Time: "<< duration << std::endl;
        std::cout << "Cout:" << cnt << std::endl;
        std::cout << "Coordinates:" << map.size() << std::endl;
        delete rregion;
        delete lregion;
    //    delete mask;
    } catch (std::exception const &exc)
    {
        std::cerr << "Exception caught: " << exc.what() << std::endl;
        return -1;
    }
    return 0;
}
