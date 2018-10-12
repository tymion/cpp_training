#pragma once
#include <cstdint>

class Mask {
    private:
        uint32_t _height;
        uint32_t _width;
        uint8_t *_mask;

    public:
        Mask(uint32_t height, uint32_t width, uint8_t *mask);
        ~Mask();

        uint8_t getMask(uint32_t height, uint32_t width);
};
