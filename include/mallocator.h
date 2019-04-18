#pragma once

#include <cstdlib>
#include <allocator.h>
#include <nullptr_allocator.h>

class Mallocator : NullPtrAllocator
{
    public:
        void deallocate(Blk& mem)
        {
            free(mem.ptr);
            mem.ptr = nullptr;
            mem.size = 0;
        }

        Blk allocate(size_t size)
        {
            return { malloc(size), size };
        }

        bool owns(Blk& mem)
        {
            return !NullPtrAllocator::owns(mem);
        }
};
