#ifndef _PIXEL_3x16_H_
#define _PIXEL_3x16_H_

#include <cstdint>
#include "pixel.h"

struct pixel_3x16 : pixel {
    uint16_t _red;
    uint16_t _green;
    uint16_t _blue;

    bool operator== (const pixel& pixel);
    bool operator!= (const pixel& pixel);
    bool operator> (const int value);
    pixel& operator- (const pixel& pixel);
    ~pixel_3x16(){};
};

#endif /* _PIXEL_3x16_H_ */
