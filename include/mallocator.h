#pragma once

#include <cstdlib>
#include <allocator.h>
#include <nullptr_allocator.h>

class Mallocator : NullPtrAllocator
{
    public:
        void
        Mallocator::deallocate(Blk& mem)
        {
            free(mem.ptr);
            NullPtrAllocator::deallocate(mem);
        }

        Blk&
        Mallocator::allocate(size_t size)
        {
            return { malloc(size), size };
        }

        bool
        Mallocator::owns(Blk& mem)
        {
            return true;
        }
};
