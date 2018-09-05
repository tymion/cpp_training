#include <stdexcept>
#include "filebuffer.h"
#include "pixel_3x8.h"
#include "pixel_4x8.h"

FileBuffer::FileBuffer(IImage *image)
{
    if (!image) {
        throw std::invalid_argument("image pointer is empty");
    }
    _image = image;
    _component = image->getComponentSize();
}

FileBuffer::~FileBuffer()
{
}

RegionBase* FileBuffer::createRegion(uint32_t height, uint32_t width)
{
    pixel **pixels = NULL;
    if (_component == 3) {
        pixels = (pixel**) new pixel_3x8*[height];
    } else if (_component == 4) {
        pixels = (pixel**) new pixel_4x8*[height];
    }
    return new Region(height, width, pixels);
}

bool FileBuffer::updateRegion(uint32_t row, uint32_t column, RegionBase *region)
{
    if (!region) {
        throw std::invalid_argument("region pointer is empty");
    }
    uint32_t neededData = _component * ((row + region->getHeight()) * _image->getWidth());
    if (_dataLen < neededData) {
        _data = (uint8_t*) realloc(_data, neededData);
        uint32_t lenDiff = neededData - _dataLen;
        if (_image->getData(&_data[_dataLen], lenDiff) != lenDiff) {
            throw std::invalid_argument("Can't read needed data");
        }
        _dataLen = neededData;
    }
    //for (uint32_t i = 0; i < region->getHeight(); i++) {
    //    region->setData(i, &_data[3 * ((row + i) * _image->getWidth() + column)]);
    //}
    return true;
}
