#pragma once

#include <cstdint>

struct pixel_3x16 {
    uint16_t _red;
    uint16_t _green;
    uint16_t _blue;

    bool operator== (const pixel_3x16& pixel);
    bool operator!= (const pixel_3x16& pixel);
    bool operator> (const int value);
    pixel_3x16& operator- (const pixel_3x16& pixel);
    ~pixel_3x16(){};
};
