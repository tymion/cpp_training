#include <stdexcept>
#include "image_processor_factory.h"

uint32_t ImageProcessorFactory::_pixel[PROCESSOR_FACTORY_SIZE];
uint32_t ImageProcessorFactory::_used = 0;

ImageProcessorFactory& ImageProcessorFactory::getInstance()
{
    static ImageProcessorFactory instance;
    return instance;
}

ImageProcessor& ImageProcessorFactory::createImageProcessor(uint32_t height, uint32_t width)
{
    uint64_t new_used = _used + height * width;
    if (new_used > PROCESSOR_FACTORY_SIZE) {
        throw std::invalid_argument("Out of memory");
    }
    ImageProcessor& img = getInstance()._warehouse.emplace_back();
    for (auto i = 0; i < height; i++) {
        img._data[i] = &_pixel[_used];
        _used += width;
    }
    return img;
}
