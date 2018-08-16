#ifndef _PIXEL_2x16_H_
#define _PIXEL_2x16_H_

#include "pixel.h"

struct pixel_2x16 : pixel {
    uint16_t color;
    uint16_t alpha;
};
#endif /* _PIXEL_2x16_H_ */
