#include <stdexcept>
#include "image_processor_factory.h"

ImageProcessorAllocator ImageProcessorFactory::_allocator;
uint32_t ImageProcessorFactory::_pixel[PROCESSOR_FACTORY_SIZE];
uint32_t ImageProcessorFactory::_used = 0;

void ImageProcessorDeleter(ImageProcessor* img)
{
    ImageProcessorFactory::deleteImageProcessor(img);
}

ImageProcessorFactory& ImageProcessorFactory::getInstance()
{
    static ImageProcessorFactory instance;
    return instance;
}

void ImageProcessorFactory::deleteImageProcessor(ImageProcessor *img)
{
    ImageProcessorFactory::_allocator.deallocate(img);
}

ImageProcessor& ImageProcessorFactory::createImageProcessor(uint32_t height, uint32_t width)
{
    uint64_t new_used = _used + height * width;
    if (new_used > PROCESSOR_FACTORY_SIZE) {
        throw std::invalid_argument("Out of memory");
    }
    ImageProcessor& img = *ImageProcessorFactory::_allocator.allocate(height);
    for (auto i = 0; i < height; i++) {
        img._data[i] = &_pixel[_used];
        _used += width;
    }
    return img;
}
