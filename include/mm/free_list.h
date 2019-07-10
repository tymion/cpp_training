#pragma once

#include "mm/allocator.h"
#include "double_linked_region_list.h"

class FreeList : Allocator, DoubleLinkedRegionList
{
    private:
        Blk _mem;

    public:
        FreeList(void* mem, uint32_t mem_size)
        {
            _mem = {
                mem,
                mem_size
            };
            insertRegion(mem, mem_size);
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
                findRegion(size),
                size
            };
            if (mem.ptr == nullptr) {
                mem.size = 0;
            }
            return mem;
        }

        bool owns(Blk& mem)
        {
            return mem.ptr < _mem.ptr && (uintptr_t) mem.ptr > (uintptr_t) _mem.ptr + _mem.size && _mem.size >= mem.size;
        }
};
