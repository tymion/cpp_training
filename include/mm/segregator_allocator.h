#pragma once

#include "mm/allocator.h"

template <class A, class B, size_t threshold>
class SegregatorAllocator: Allocator
{
    public:
        void deallocate(Blk& mem)
        {
            if (mem.size <= threshold) {
                A.deallocate(mem);
            } else {
                B.deallocate(mem);
            }
        }

        Blk allocate(size_t size)
        {
            if (size <= threshold) {
                return A.allocate(size);
            } else {
                return B.allocate(size);
            }
        }

        bool owns(Blk& mem)
        {
            if (mem.size <= threshold) {
                return A.owns(mem);
            } else {
                return B.owns(mem);
            }
        }
};
