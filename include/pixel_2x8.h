#ifndef _PIXEL_2x8_H_
#define _PIXEL_2x8_H_

#include "pixel.h"

struct pixel_2x8 : pixel {
    uint8_t color;
    uint8_t alpha;
};
#endif /* _PIXEL_2x8_H_ */
