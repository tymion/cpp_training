#pragma once

#include "mm/fixed_size_allocator.h"
#include "mm/allocator.h"

class NullPtrAllocator : Allocator, public FixedSizeAllocator {
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

        bool deallocate(void* ptr)
        {
            if (ptr) {
                return true;
            }
            return false;
        }

        void* allocate()
        {
            return nullptr;
        }

        bool owns(void* ptr)
        {
            if (ptr == nullptr) {
                return true;
            }
            return false;
        }
};
