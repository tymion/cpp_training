#ifndef _IMAGE_HPP_
#define _IMAGE_HPP_
#include <cstdint>
#include <iostream>

class IImage
{
    public:
        virtual uint32_t getHeight() = 0;
        virtual uint32_t getWidth() = 0;
        virtual ~IImage(){};
};

#endif /* _IMAGE_HPP_ */
