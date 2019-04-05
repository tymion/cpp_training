#pragma once

#include <allocator.h>

template<class A, typename T, size_t N, size_t blk_size>
class StackAllocator : Allocator {
    T _stack[N*blk_size];
    size_t _cur_blk;
    A fallback;

    public:
        void deallocate(Blk& mem)
        {
            if (size == blk_size && mem.ptr == _stack[N*(_cur_blk - 1)]) {
                _cur_blk--;
            } else {
                fallback.deallocate(mem);
            }
        }

        Blk& allocate(size_t size)
        {
            Blk& mem = fallback.allocate(size);
            if (mem.ptr) {
                return mem;
            }

            if (size != blk_size || _cur_blk == N) {
                return { nullptr, 0 };
            }

            return { _stack[N*_cur_blk++], size };
        }

        bool owns(Blk& mem)
        {
            if (mem.ptr >= _stack && _stack + N*blk_size < mem.ptr) {
                return true;
            }
            return false;
        }
};
