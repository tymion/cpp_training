#include <string>
#include <cstring>
#include <exception>
#include <iostream>
#include "loader.hpp"
#include "filebuffer.hpp"

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
        Region *region = new Region(size, size, mask);
        for (uint32_t row = 0; row < height; row++) {
            for (uint32_t col = 0; col < width; col++) {
                lbuffer->getData(row, col, region);
            }
        }
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
