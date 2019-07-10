#pragma once

#include <cstdint>

#include "color_space.h"
#include "image.h"

class ImageProcessor : public Matrix<uint32_t>
{
    private:
        uint32_t **_ext = nullptr;
    public:
        ImageProcessor(uint32_t height, uint32_t width, uint32_t **data);
        ImageProcessor(uint32_t height, uint32_t width, uint32_t **data, uint32_t **ext);
        ImageSharedPtr changeColorSpace(ImageSharedPtr const img, ColorSpace color);
        ImageSharedPtr lowPassFilter(ImageSharedPtr const img, uint8_t kernel_size);
        void horizontalConvolution(ImageSharedPtr const in, ImageSharedPtr out, uint32_t height, uint32_t width,
                                    uint8_t kernel_size);
        void verticalConvolution(ImageSharedPtr const in, ImageSharedPtr out, uint32_t height, uint32_t width,
                                    uint8_t kernel_size);
        void boxConvolution(ImageSharedPtr const in, ImageSharedPtr out, uint32_t height, uint32_t width,
                                    uint8_t kernel_size);
        void fastGaussianConvolution(ImageSharedPtr const in, ImageSharedPtr out, uint32_t height, uint32_t width,
                                        uint8_t kernel_size);
        ImageSharedPtr gaussian(ImageSharedPtr const in, uint8_t kernel_size);
        ImageSharedPtr standardDeviation(ImageSharedPtr const first, ImageSharedPtr const second, uint8_t kernel_size);
        ImageSharedPtr subtraction(ImageSharedPtr const first, ImageSharedPtr const second);
};

template<size_t H, size_t W>
class StackImageProcessor: public ImageProcessor
{
    private:
        uint32_t _stack_data[H * W] = {};
        uint32_t * _stack_tab[H] = {};
        uint32_t _ext_data[H][W] = {};

    public:
        StackImageProcessor() : ImageProcessor(H, W,
                                reinterpret_cast<uint32_t**>(&_stack_tab),
                                reinterpret_cast<uint32_t**>(_ext_data))
        {
            for (uint32_t i = 0; i < H; i++) {
                _stack_tab[i] = &_stack_data[i * W];
            }
        }
};

class HeapImageProcessor : public ImageProcessor
{
    public:
        HeapImageProcessor(uint32_t height, uint32_t width, uint32_t **data, uint32_t **ext) :
                    ImageProcessor(height, width, data, ext)
        {
        }
};
