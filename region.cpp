#include <stdexcept>
#include "region.h"
#include "config.h"
#include "pixel.h"

uint32_t RegionBase::getHeight()
{
    return _height;
}

uint32_t RegionBase::getWidth()
{
    return _width;
}

void RegionBase::setMask(Mask *mask)
{
    _mask = mask;
}

template<typename T>
Region<T>::Region(uint32_t height, uint32_t width, pixel<T> *data[], Mask *mask)
{
    if (height == 0 || width == 0) {
        throw std::invalid_argument("Check input");
    }
    _height = height;
    _width = width;
    _mask = mask;
    _data = data;
}

template<typename T>
Region<T>::Region(uint32_t height, uint32_t width, pixel<T> *data[])
{
    if (height == 0 || width == 0) {
        throw std::invalid_argument("Check input");
    }
    _height = height;
    _width = width;
    _mask = NULL;
    _data = data;
}

template<typename T>
Region<T>::~Region()
{
    delete [] _data;
}

template<typename T>
void Region<T>::setData(uint32_t height, uint8_t *data)
{
    _data[height] = dynamic_cast<const *T>(data);
}

template<typename T>
bool Region<T>::operator== (const RegionBase& region)
{
    T&  regionT = dynamic_cast<T&>(region);
#ifdef INDEX_JACARDA
    uint32_t similar = 0;
    uint32_t different = 0;

    for (uint32_t i = 0; i < _height; i++) {
        for (uint32_t j = 0; j < _width; j++) {
            if (_mask->getMask(i, j) == 0) {
                continue;
            }
            if ((_data[i][j] - regionT._data[i][j]) < similarityThreshold) {
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
            if (_data[i][j] != regionT._data[i][j]) {
                return false;
            }
        }
    }
    return true;
#endif
}
