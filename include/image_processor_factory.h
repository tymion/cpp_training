#pragma once

#include "config.h"

#define PROCESSOR_FACTORY_SIZE DATA_HEIGHT * DATA_WIDTH * IMAGE_COMPONENT * 2
#define PROCESSOR_SIZE DATA_HEIGHT

class ImageProcessor
{
    friend class ImageProcessorFactory;
    private:
        ImageProcessor () {}

        uint8_t* _data[PROCESSOR_SIZE];

    public:
        ImageProcessor(ImageProcessor const&) = delete;
        void operator=(ImageProcessor const&) = delete;
};

class ImageProcessorFactory
{
    private:
        ImageProcessorFactory () {}

        static ImageProcessorFactory& getInstance();

        static uint8_t _pixel[PROCESSOR_FACTORY_SIZE];
        static uint32_t _used;

    public:
        static ImageProcessor& createImageProcessor();

        ImageProcessorFactory(ImageProcessorFactory const&) = delete;
        void operator=(ImageProcessorFactory const&) = delete;
};
