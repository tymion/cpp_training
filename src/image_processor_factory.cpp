#include <stdexcept>
#include "image_processor_factory.h"

ImageProcessorAllocator ImageProcessorFactory::_allocator;

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
    return *ImageProcessorFactory::_allocator.allocate();
}
