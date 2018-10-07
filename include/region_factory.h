#ifndef _FILE_BUFFER_H_
#define _FILE_BUFFER_H_
#include <cstdbool>
#include <memory>
#include "iimage.h"
#include "region.h"

class RegionFactory {
    private:
        std::shared_ptr<IImage> _image;
        uint8_t _component;

    public:
        RegionFactory(std::shared_ptr<IImage> &image);
        RegionBase* createRegion(uint32_t height, uint32_t width);
        bool updateRegion(uint32_t row, uint32_t column, RegionBase *region);
};

#endif /* _FILE_BUFFER_H_ */
