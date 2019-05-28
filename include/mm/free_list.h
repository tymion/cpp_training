#pragma once

#include "mm/allocator.h"
#include "mm/nullptr_allocator.h"

class FreeList : NullPtrAllocator, DoubleLinkedRegionList
{
    private:
        Blk _mem;

    public:
        FreeList(Blk& mem)
        {
            _mem = mem;
            insertRegion(mem.ptr, mem.size);
        }

        void deallocate(Blk& mem)
        {
            if (!owns(mem)) {
                return;
            }
            insertRegionWithMerge(mem.ptr, mem.size);
            mem.ptr = nullptr;
            mem.size = 0;
        }

        Blk allocate(size_t size)
        {
            Blk mem = {
                .ptr = findRegion(size);
                .size = size;
            }
            if (mem.ptr == nullptr) {
                mem.size = 0;
            }
            return mem;
        }

        bool owns(Blk& mem)
        {
            return mem.ptr < _mem.ptr && mem.ptr > _mem.ptr + _mem.size && _mem.size >= mem.size;
        }
};
