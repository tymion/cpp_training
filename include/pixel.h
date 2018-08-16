#ifndef _PIXEL_H_
#define _PIXEL_H_

struct pixel
{
    virtual pixel& operator-(const pixel& pixel) = 0;
    virtual bool operator==(const pixel& pixel) = 0;
    virtual bool operator!=(const pixel& pixel) = 0;
    virtual bool operator> (const int value) = 0;
    virtual ~pixel(){};
};

#endif /* _PIXEL_H_ */
