#include <stdexcept>
#include <cstring>
#include "mask.h"

Mask::Mask(uint32_t height, uint32_t width, uint8_t *mask) {
    if (height == 0 || width == 0 || mask == NULL) {
        throw std::invalid_argument("Check input");
    }
    _width = width;
    _height = height;
    _mask = new uint8_t[height * width];
    if (_mask == NULL) {
        throw std::invalid_argument("Allocating mem failed");
    }
    std::memcpy(_mask, mask, height * width * sizeof(uint8_t));
}

Mask::~Mask() {
    delete [] _mask;
}

uint8_t Mask::getMask(uint32_t height, uint32_t width)
{
    return _mask[_width * height + width];
}
