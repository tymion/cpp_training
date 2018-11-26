#include <cstdlib>
#include "image_factory.h"

Image::Image(uint32_t height)
{
    _data = (uint8_t**) malloc(height * sizeof(_data));
}

uint32_t Image::getWidth()
{
    return _width;
}

uint32_t Image::getHeight()
{
    return _height;
}
