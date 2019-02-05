#include "image_processor_factory.h"

uint8_t ImageProcessorFactory::_pixel[PROCESSOR_FACTORY_SIZE];
uint32_t ImageProcessorFactory::_used = 0;

ImageProcessorFactory& ImageProcessorFactory::getInstance()
{
    static ImageProcessorFactory instance;
    return instance;
}

ImageProcessor& ImageProcessorFactory::createImageProcessor()
{
    ImageProcessor img;
    for (auto i = 0; i < PROCESSOR_SIZE; i++) {
        img._data[i] = &_pixel[_used + i * DATA_WIDTH];
    }
    return img;
}
