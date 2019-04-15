#pragma once

#include <allocator.h>

template<typename A, typename B>
class FallbackAllocator : Allocator
{
    A _main;
    B _fallback;

    public:
        void deallocate(Blk& mem) {
            _main.deallocate(mem);
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
            return _main.owns(mem) || _fallback.owns(mem);
        }
};
