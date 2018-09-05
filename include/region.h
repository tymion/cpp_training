#ifndef _REGION_H_
#define _REGION_H_
#include "mask.h"
#include "pixel.h"

class RegionBase {
    protected:
        uint32_t _height;
        uint32_t _width;
        Mask *_mask;

    public:
        uint32_t getHeight();

        uint32_t getWidth();

        void setMask(Mask *mask);

        virtual void setData(uint32_t height, uint8_t *data);

        virtual bool operator== (const RegionBase& region);
};

template<typename T>
class Region : RegionBase {
    private:
        T **_data;

    public:
        Region(uint32_t height, uint32_t width, pixel<T> *data[], Mask *mask);

        Region(uint32_t height, uint32_t width, pixel<T> *data[]);

        ~Region();

        void setData(uint32_t height, uint8_t *data);

        bool operator== (const RegionBase& region);
};
#endif /* _REGION_H_ */
