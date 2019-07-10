#pragma once

#include "mm/allocator.h"

template<class T>
class HeapImageAllocator : Allocator
{
    public:
        void deallocate(Blk& mem)
        {
        }

        Blk allocate(size_t size)
        {
        }

        bool owns(Blk& mem)
        {
        }
};
