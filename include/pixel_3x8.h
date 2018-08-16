#ifndef _PIXEL_3x8_H_
#define _PIXEL_3x8_H_

#include <cstdint>
#include "pixel.h"

struct pixel_3x8 : pixel {
    uint8_t _red;
    uint8_t _green;
    uint8_t _blue;

    bool operator== (const pixel& pixel);
    bool operator!= (const pixel& pixel);
    bool operator> (const int value);
    pixel& operator- (const pixel& pixel);
    ~pixel_3x8(){};
};

#endif /* _PIXEL_3x8_H_ */
