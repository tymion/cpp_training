#pragma once

#include "image_processor.h"
#include "object_allocator.h"

template<size_t N, size_t H, size_t W>
class ImageProcessorAllocator: ObjectAllocator<StackImageProcessor<H, W>, N>
{
    public:
        ImageProcessor* allocate()
        {
            return new (ObjectAllocator<StackImageProcessor<H, W>, N>::allocate()) StackImageProcessor<H, W>();
        }

	void deallocate(ImageProcessor *ptr)
	{
            ObjectAllocator<StackImageProcessor<H, W>, N>::deallocate(static_cast<StackImageProcessor<H, W>*>(ptr));
	}
};
