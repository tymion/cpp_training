#ifndef _FILE_BUFFER_H_
#define _FILE_BUFFER_H_
#include <cstdbool>
#include <memory>
#include "iimage.h"
#include "region.h"

using namespace std;

class RegionFactory {
    private:
        shared_ptr<IImage> _image;
        uint8_t _component;

    public:
        RegionFactory(shared_ptr<IImage> &image);
        RegionBase* createRegion(uint32_t height, uint32_t width);
        bool updateRegion(uint32_t row, uint32_t column, unique_ptr<RegionBase> const& region);
};

#endif /* _FILE_BUFFER_H_ */
