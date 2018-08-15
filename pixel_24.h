#ifndef _PIXEL_24_H_
#define _PIXEL_24_H_

#include <cstdint>
#include "pixel.h"

struct pixel_24 : pixel {
    uint8_t _red;
    uint8_t _green;
    uint8_t _blue;

    bool operator== (const pixel& pixel);
    bool operator!= (const pixel& pixel);
//    template <typename T>
    bool operator> (const int value);
    pixel& operator- (const pixel& pixel);
    ~pixel_24(){};
};

#endif /* _PIXEL_24_H_ */
