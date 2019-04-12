#pragma once

#include <allocator.h>

template<typename A, typename B>
class FallbackAllocator : Allocator
{
    A main;
    B fallback;

    public:
        void deallocate(Blk& mem) {
            main.deallocate(mem);
            if (mem.ptr != nullptr) {
                _fallback.deallocate(mem);
            }
        }
        Blk allocate(size_t size)
        {
            Blk mem = _main.allocate(size);
            if (mem.ptr == nullptr) {
                mem = _fallback(size);
            }
        }
        bool owns(Blk& mem) {
            return main.owns(mem) || fallback.owns(mem);
        }
};
