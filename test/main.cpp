#include <iostream>
#include "pixel.h"
#include "pixel_24.h"

int main()
{
    pixel_24 *pix1 = new pixel_24();
    pix1->_red = 3;
    pix1->_green = 30;
    pix1->_blue = 50;
    pixel_24 *pix2 = new pixel_24();
    pix2->_red = 1;
    pix2->_green = 10;
    pix2->_blue = 100;
    pixel *p2 = (pixel*) pix2;
    pixel *p1 = (pixel*) pix1;
    if (*p1 - *p2 > 1)
        std::cout << "Pix" << std::endl;
    else
        std::cout << "Pix2" << std::endl;
    delete pix1;
    delete pix2;

    return 0;
}
