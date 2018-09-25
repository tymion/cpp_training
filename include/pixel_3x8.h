#ifndef _PIXEL_3x8_H_
#define _PIXEL_3x8_H_

#include <cstdint>
#include <iostream>

struct pixel_3x8 {
    uint8_t _red;
    uint8_t _green;
    uint8_t _blue;

    bool operator== (const pixel_3x8& pixel);
    bool operator!= (const pixel_3x8& pixel);
    bool operator> (const int value);
    bool operator< (const int value);
    friend std::ostream & operator<< (std::ostream &stream, const pixel_3x8 &s);
    pixel_3x8 operator- (const pixel_3x8& pixel);
    ~pixel_3x8(){};
};

#endif /* _PIXEL_3x8_H_ */
