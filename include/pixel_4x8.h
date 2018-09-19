#ifndef _PIXEL_4x8_H_
#define _PIXEL_4x8_H_
#include <iostream>

struct pixel_4x8 {
    uint8_t _red;
    uint8_t _green;
    uint8_t _blue;
    uint8_t _alpha;

    bool operator== (const pixel_4x8& pixel);
    bool operator!= (const pixel_4x8& pixel);
    bool operator> (const int value);
    //std::ostream& operator<< (std::ostream& stream);
    friend std::ostream & operator<< (std::ostream &stream, const pixel_4x8 &s);
    pixel_4x8& operator- (const pixel_4x8& pixel);
    ~pixel_4x8(){};
};

#endif /* _PIXEL_4x8_H_ */