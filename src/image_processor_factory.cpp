#include <stdexcept>
#include "image_processor_factory.h"

uint32_t ImageProcessorFactory::_pixel[PROCESSOR_FACTORY_SIZE];
uint32_t ImageProcessorFactory::_used = 0;

ImageProcessorFactory& ImageProcessorFactory::getInstance()
{
    static ImageProcessorFactory instance;
    return instance;
}

ImageProcessor& ImageProcessorFactory::createImageProcessor()
{
    if (_used + PROCESSOR_SIZE * DATA_WIDTH > PROCESSOR_FACTORY_SIZE) {
        throw std::invalid_argument("Out of memory");
    }
    ImageProcessor& img = getInstance()._warehouse.emplace_back();
    for (auto i = 0; i < PROCESSOR_SIZE; i++) {
        img._data[i] = &_pixel[_used + i * DATA_WIDTH];
    }
    _used += PROCESSOR_SIZE * DATA_WIDTH;
    return img;
}
