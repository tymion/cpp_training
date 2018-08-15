#include <stdexcept>
#include "Region.hpp"
#include "config.h"
#include "pixel.h"

Region::Region(uint32_t height, uint32_t width, pixel *data[], Mask *mask)
{
    if (height == 0 || width == 0) {
        throw std::invalid_argument("Check input");
    }
    _height = height;
    _width = width;
    _mask = mask;
    _data = data;
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

void Region::setData(uint32_t height, pixel *data)
{
    _data[height] = data;
}

bool Region::operator== (const Region& region)
{
#ifdef INDEX_JACARDA
    uint32_t similar = 0;
    uint32_t different = 0;

    for (uint32_t i = 0; i < _height; i++) {
        for (uint32_t j = 0; j < _width; j++) {
            if (_mask->getMask(i, j) == 0) {
                continue;
            }
            if ((_data[i][j] - region._data[i][j]) < similarityThreshold) {
                similar++;
            } else {
                different++;
            }
        }
    }
    return similar / (similar + different) < jacardThreshold;
#else
    for (uint32_t i = 0; i < _height; i++) {
        for (uint32_t j = 0; j < _width; j++) {
            if (_mask->getMask(i, j) == 0) {
                continue;
            }
            if (_data[i][j] != region._data[i][j]) {
                return false;
            }
        }
    }
    return true;
#endif
}
