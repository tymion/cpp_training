#pragma once

#include <cstdint>
#include <vector>

#include "config.h"
#include "color_space.h"
#include "image_factory.h"

#define PROCESSOR_FACTORY_SIZE DATA_HEIGHT * DATA_WIDTH * IMAGE_COMPONENT * 2
#define PROCESSOR_SIZE DATA_HEIGHT

class ImageProcessor;

using ImageProcessorAllocator = ObjectAllocator<ImageProcessor, IMAGE_ALLOCATOR_POOL_SIZE>;

class ImageProcessor
{
    friend class ImageProcessorFactory;
    friend ImageProcessorAllocator;

    private:
        uint32_t _data[300][600];

    public:
        Image& changeColorSpace(Image const& img, ColorSpace color);
        Image& lowPassFilter(Image const& img, uint8_t kernel_size);
        void horizontalConvolution(Image const& in, Image& out, uint32_t height, uint32_t width,
                                    uint8_t kernel_size);
        void verticalConvolution(Image const& in, Image& out, uint32_t height, uint32_t width,
                                    uint8_t kernel_size);
        void boxConvolution(Image const& in, Image& out, uint32_t height, uint32_t width,
                                    uint8_t kernel_size);
        void fastGaussianConvolution(Image const& in, Image& out, uint32_t height, uint32_t width,
                                        uint8_t kernel_size);
        Image& standardDeviation(Image const& first, Image const& second, uint8_t kernel_size);
        Image& subtraction(Image const& first, Image const& second);
};

void ImageProcessorDeleter(ImageProcessor* img);

class ImageProcessorFactory
{
    private:
        static ImageProcessorAllocator _allocator;

        ImageProcessorFactory() {}

        static ImageProcessorFactory& getInstance();

    public:
        static ImageProcessor& createImageProcessor();
        static void deleteImageProcessor(ImageProcessor* img);

        ImageProcessorFactory(ImageProcessorFactory const&) = delete;
        void operator=(ImageProcessorFactory const&) = delete;
};
