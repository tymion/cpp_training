#pragma once

#include <cstdint>

#include "color_space.h"
#include "image.h"

class ImageProcessor
{
    protected:
        uint32_t **_data = nullptr;

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
        Image& gaussian(Image const& in, uint8_t kernel_size);
        Image& standardDeviation(Image const& first, Image const& second, uint8_t kernel_size);
        Image& subtraction(Image const& first, Image const& second);
};

template<size_t H, size_t W>
class StackImageProcessor: ImageProcessor
{
    private:
        uint32_t _stack_data[H][W] = {};

    public:
        StackImageProcessor()
        {
            ImageProcessor::_data = _stack_data;
        }
};
