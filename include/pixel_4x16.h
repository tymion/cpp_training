#ifndef _PIXEL_4x16_H_
#define _PIXEL_4x16_H_

#include "pixel.h"

struct pixel_4x16 : pixel {
    uint16_t red;
    uint16_t green;
    uint16_t blue;
    uint16_t alpha;
};
#endif /* _PIXEL_4x16_H_ */
