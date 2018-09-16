#include <string>
#include <cstring>
#include <exception>
#include <iostream>
#include "region.h"
#include "loader.h"
#include "filebuffer.h"

using namespace std;

#define size 7

int main() {
    string leftFile = "left.png";
    string rightFile = "left.png";
    //string rightFile = "right.png";
    try {
        Loader *loader = new Loader();
        IImage *lImage = loader->loadImage(leftFile);
        IImage *rImage = loader->loadImage(rightFile);
        uint32_t height = lImage->getHeight();
        uint32_t width = lImage->getWidth();
        height = 10;
        FileBuffer *lbuffer = new FileBuffer(lImage);
        FileBuffer *rbuffer = new FileBuffer(rImage);
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
                uint32_t s_row_max = row + size + 3 > height ? height - size : row + size + 3;
                if (row % 10 == 0 && col % 10 == 0) {
                    std::cout << "Step:" << row << "|" << col << std::endl;
                    std::cout << "Step1:" << s_row << "|" << s_row_max << std::endl;
                }
                for (; s_row < s_row_max; s_row++) {
                    if (s_row % 10 == 0) {
                        std::cout << "SubStep:" << s_row << "|" << std::endl;
                    }
                    for (uint32_t s_col = col; s_col < width - size; s_col++) {
                        if (s_row % 10 == 0 && s_col % 10 == 0) {
                            std::cout << "SubStep:" << s_row << "|" << s_col << std::endl;
                        }
                        lbuffer->updateRegion(s_row, s_col, lregion);
                        if (*rregion == *lregion) {
                            cnt++;
                        }
                    }
                }
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
