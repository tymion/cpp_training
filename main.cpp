#include <string>
#include <cstring>
#include <exception>
#include <iostream>
#include "region.h"
#include "loader.h"
#include "filebuffer.h"

using namespace std;

#define SIZE 7

int main() {
    string leftFile = "left.png";
    string rightFile = "right.png";
    try {
        Loader *loader = new Loader();
        IImage *lImage = loader->loadImage(leftFile);
        IImage *rImage = loader->loadImage(rightFile);
        uint32_t height = lImage->getHeight();
        uint32_t width = lImage->getWidth();
        FileBuffer *lbuffer = new FileBuffer(lImage);
        FileBuffer *rbuffer = new FileBuffer(rImage);
        uint32_t size = SIZE;
        uint8_t maskData[SIZE*SIZE];
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
                uint32_t s_row = row - 3 < 0 ? 0 : row - 3;
                uint32_t s_row_max = row + size + 3 > height ? row + size : row + size + 3;
                for (; s_row < s_row_max; s_row++) {
                    for (uint32_t s_col = col; s_col < width; s_col++) {
                        lbuffer->updateRegion(s_row, s_col, lregion);
                        if (rregion == lregion) {
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
    } catch (std::exception const &exc)
    {
        std::cerr << "Exception caught: " << exc.what() << std::endl;
        return -1;
    }
    return 0;
}
