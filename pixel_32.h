#ifndef _PIXEL_32_H_
#define _PIXEL_32_H_

#include "pixel.h"

struct pixel_32 : pixel {
    uint8_t red;
    uint8_t green;
    uint8_t blue;
    uint8_t alpha;
};
#endif /* _PIXEL_32_H_ */
