#include <stdexcept>
#include "image_processor_factory.h"

ImageProcessorAlloc ImageProcessorFactory::_allocator;

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

ImageProcessor& ImageProcessorFactory::createImageProcessor()
{
    return *ImageProcessorFactory::_allocator.allocate();
}
