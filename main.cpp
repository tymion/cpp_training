#include <string>
#include <cstring>
#include <exception>
#include <iostream>
#include "region.h"
#include "loader.h"
#include "region_factory.h"

using namespace std;

#define size 7

int main() {
    string leftFile = "resources/left.png";
    //string rightFile = "resources/left.png";
    string rightFile = "resources/right.png";
    try {
        Loader *loader = new Loader();
        IImage *lImage = loader->loadImage(leftFile);
        IImage *rImage = loader->loadImage(rightFile);
        uint32_t height = lImage->getHeight();
        uint32_t width = lImage->getWidth();
        RegionFactory *lbuffer = new RegionFactory(lImage);
        RegionFactory *rbuffer = new RegionFactory(rImage);
        uint8_t maskData[size*size];
        std::memset(maskData, 1, sizeof(maskData));
        Mask *mask = new Mask(size, size, maskData); 
        RegionBase *rregion = rbuffer->createRegion(size, size);
        RegionBase *lregion = lbuffer->createRegion(size, size);
        rregion->setMask(mask);
        lregion->setMask(mask);
        uint32_t cnt = 0;
        for (uint32_t row = 0; row < height - size; row++) {
            for (uint32_t col = 0; col < width - size; col++) {
                rbuffer->updateRegion(row, col, rregion);
                uint32_t s_row = (int32_t) row - 3 < 0 ? 0 : (int32_t) row - 3;
                uint32_t s_row_max = row + 3 > height - size ? height - size : row + 3;
                for (; s_row < s_row_max; s_row++) {
#ifdef DEBUG
                    if (s_row % 10 == 0) {
                        std::cout << "SubStep:" << s_row << "||" << s_row_max << std::endl;
                    }
#endif
                    for (uint32_t s_col = col; s_col < width - size; s_col++) {
#ifdef DEBUG
                        std::cout << "SubStep:" << s_row << "||" << s_row_max << "|" << s_col << std::endl;
#endif
                        lbuffer->updateRegion(s_row, s_col, lregion);
                        if (*rregion == *lregion) {
                            cnt++;
                        }
                    }
                }
                std::cout << "SubStep4:" << s_row << "||" << s_row_max << std::endl;
            }
        }
        std::cout << "Cout:" << cnt << std::endl;
        delete lImage;
        delete rImage;
        delete loader;
        delete lbuffer;
        delete rbuffer;
        delete rregion;
        delete lregion;
        delete mask;
    } catch (std::exception const &exc)
    {
        std::cerr << "Exception caught: " << exc.what() << std::endl;
        return -1;
    }
    return 0;
}
