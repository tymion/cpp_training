#include <cstdlib>
#include "image_storage_factory.h"

ImageStorage::ImageStorage(uint32_t height)
{
    _data = (uint8_t**) malloc(height * sizeof(_data));
}

uint32_t ImageStorage::getWidth()
{
    return _width;
}

uint32_t ImageStorage::getHeight()
{
    return _height;
}
