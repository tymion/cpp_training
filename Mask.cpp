#include <stdexcept>
#include "Mask.hpp"

Mask::Mask(uint32_t height, uint32_t width, uint8_t *mask) {
    if (height == 0 || width == 0 || mask == NULL) {
        throw std::invalid_argument("Check input");
    }
    _mask = new uint8_t(height * width);
    if (_mask == NULL) {
        throw std::invalid_argument("Allocating mem failed");
    }
    for (uint32_t i = 0; i < height * width; i++) {
        _mask[i] = mask[i];
    }
}

Mask::~Mask() {
    delete [] _mask;
}

uint8_t Mask::getMask(uint32_t height, uint32_t width)
{
    return _mask[_width * height + width];
}