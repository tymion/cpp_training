#include <stdexcept>
#include "filebuffer.hpp"

FileBuffer::FileBuffer(IImage *image)
{
    if (!image) {
        throw std::invalid_argument("image pointer is empty");
    }
    _image = image;
}

FileBuffer::~FileBuffer()
{
}

bool FileBuffer::getData(uint32_t row, uint32_t column, Region *region)
{
    if (!region) {
        throw std::invalid_argument("region pointer is empty");
    }
    uint32_t neededData = 3 * ((row + region->getHeight()) * _image->getWidth());
    if (_dataLen < neededData) {
        _data = (uint8_t*) realloc(_data, neededData);
        uint32_t lenDiff = neededData - _dataLen;
        if (_image->getData(&_data[_dataLen], lenDiff) != lenDiff) {
            throw std::invalid_argument("Can't read needed data");
        }
        _dataLen = neededData;
    }
    for (uint32_t i = 0; i < region->getHeight(); i++) {
        region->setData(i, &_data[3 * ((row + i) * _image->getWidth() + column)]);
    }
    return true;
}
