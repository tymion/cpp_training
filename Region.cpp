#include <stdexcept>
#include "Region.hpp"

Region::Region(uint32_t height, uint32_t width, Mask *mask)
{
    if (height == 0 || width == 0) {
        throw std::invalid_argument("Check input");
    }
    _height = height;
    _width = width;
    _mask = mask;
    _data = new uint8_t*[height];
}

Region::~Region()
{
    delete [] _data;
}

uint32_t Region::getHeight()
{
    return _height;
}

uint32_t Region::getWidth()
{
    return _width;
}

void Region::setData(uint32_t height, uint8_t *data)
{
    _data[height] = data;
}
