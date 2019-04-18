#pragma once

#include <cstdint>
#include <vector>

#include "config.h"
#include "color_space.h"
#include "image_factory.h"

#define PROCESSOR_FACTORY_SIZE DATA_HEIGHT * DATA_WIDTH * IMAGE_COMPONENT * 2
#define PROCESSOR_SIZE DATA_HEIGHT

class ImageProcessor
{
    friend class ImageProcessorFactory;
    friend struct ImageProcessorAllocator;

    private:
        uint32_t* _data[PROCESSOR_SIZE];

        ImageProcessor () {}

    public:
        Image& changeColorSpace(Image const& img, ColorSpace color);
        Image& lowPassFilter(Image const& img, uint8_t kernel_size);
        Image& standardDeviation(Image const& first, Image const& second, uint8_t kernel_size);
        Image& subtraction(Image const& first, Image const& second);
};

class ImageProcessorFactory
{
    struct ImageProcessorAllocator: std::allocator<ImageProcessor>
    {
        template<class U, class... Args>
        void construct(U *u, Args&&... args)
        {
            new((void*)u) U(std::forward<Args>(args)...);
        }
        template<class U>
        struct rebind
        {
            typedef ImageProcessorAllocator other;
        };
    };

    private:
        static uint32_t _pixel[PROCESSOR_FACTORY_SIZE];
        static uint32_t _used;
        std::vector<ImageProcessor, ImageProcessorAllocator> _warehouse;

        ImageProcessorFactory() {}

        static ImageProcessorFactory& getInstance();

    public:
        static ImageProcessor& createImageProcessor();

        ImageProcessorFactory(ImageProcessorFactory const&) = delete;
        void operator=(ImageProcessorFactory const&) = delete;
};
