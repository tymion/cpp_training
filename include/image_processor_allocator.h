#pragma once

#include "image_processor.h"

template<size_t N, size_t H, size_t W>
class ImageProcessorAllocator: ObjectAllocator<ImageProcessor<H, W>, N>
{
    public:
        ImageProcessor* allocate()
        {
            return new (ObjectAllocator<ImageProcessor<H, W>, N>::allocate(sizeof(ImageProcessor<H, W>))) ImageProcessor<H, W>();
        }
};
