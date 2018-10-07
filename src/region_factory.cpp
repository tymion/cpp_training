#include <stdexcept>
#include "region_factory.h"
#include "pixel_3x8.h"
#include "pixel_4x8.h"

RegionFactory::RegionFactory(std::shared_ptr<IImage> &image)
{
    if (!image) {
        throw std::invalid_argument("image pointer is empty");
    }
    _image = image;
    _component = image->getComponentCnt();
}

RegionBase* RegionFactory::createRegion(uint32_t height, uint32_t width)
{
    if (_component == 3) {
        return (RegionBase*) new Region<pixel_3x8>(height, width);
    } else if (_component == 4) {
        return (RegionBase*) new Region<pixel_4x8>(height, width);
    } else {
        throw std::invalid_argument("Unsupported component.");
    }
}

bool RegionFactory::updateRegion(uint32_t row, uint32_t column, RegionBase *region)
{
    if (!region) {
        throw std::invalid_argument("region pointer is empty");
    }
    uint8_t *data = NULL;
    for (uint32_t i = 0; i < region->getHeight(); i++) {
        if (!_image->getData(row + i, &data)) {
            throw std::invalid_argument("Can't read needed data");
        }
        region->setData(i, &data[_component * column]);
    }
    return true;
}
