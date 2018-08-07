#ifndef _REGION_HPP_
#define _REGION_HPP_
#include "Mask.hpp"

class Region {
    private:
        uint32_t _height;
        uint32_t _width;
        uint8_t **_data;
        Mask *_mask;

    public:
        Region(uint32_t height, uint32_t width, Mask *mask);
        ~Region();

        uint32_t getHeight();

        uint32_t getWidth();

        void setData(uint32_t height, uint8_t *data);

        bool operator== (const Region& region);
};
#endif /* _REGION_HPP_ */
