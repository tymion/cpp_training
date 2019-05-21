#pragma once

#include <cstdint>

#include "config.h"
#include "image_processor.h"
#include "image_processor_allocator.h"

#define PROCESSOR_FACTORY_SIZE DATA_HEIGHT * DATA_WIDTH * IMAGE_COMPONENT * 2
#define PROCESSOR_SIZE DATA_HEIGHT

class Configuration;

void ImageProcessorDeleter(ImageProcessor* img);

using ImageProcessorAlloc = ImageProcessorAllocator<Configuration::getStorageSize(),
                                                    Configuration::getImageHeight(),
                                                    Configuration::getImageWidth()>;
class ImageProcessorFactory
{
    private:
        static ImageProcessorAlloc _allocator;

        ImageProcessorFactory() {}

        static ImageProcessorFactory& getInstance();

    public:
        static ImageProcessor& createImageProcessor();
        static void deleteImageProcessor(ImageProcessor* img);

        ImageProcessorFactory(ImageProcessorFactory const&) = delete;
        void operator=(ImageProcessorFactory const&) = delete;
};
