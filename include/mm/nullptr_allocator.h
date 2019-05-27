#pragma once

#include "mm/allocator.h"

class NullPtrAllocator : Allocator {
    public:
        void deallocate(Blk& mem)
        {
            if (mem.ptr == nullptr) {
                mem.size = 0;
            }
        }

        Blk allocate(size_t size)
        {
            (void) size;
            return { nullptr, 0 };
        }

        bool owns(Blk& mem)
        {
            if (mem.size == 0 && mem.ptr == nullptr) {
                return true;
            }
            return false;
        }
};
