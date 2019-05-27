#pragma once

#include "image.h"
#include "object_allocator.h"

template<size_t N, size_t H, size_t W>
class ImageAllocator: ObjectAllocator<StackImage<H, W>, N>
{
    public:
        Image* allocate()
        {
            return new (ObjectAllocator<StackImage<H, W>, N>::allocate()) StackImage<H, W>();
        }

	void deallocate(Image *ptr)
	{
            ObjectAllocator<StackImage<H, W>, N>::deallocate(static_cast<StackImage<H, W>*>(ptr));
	}
};
