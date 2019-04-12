#pragma once

#include <allocator.h>
#include <nullptr_allocator.h>

template<typename T, size_t N, size_t blk_size>
class StackAllocator : NullPtrAllocator
{
    T _stack[N*blk_size];
    size_t _cur_blk = 0;

    public:
        void deallocate(Blk& mem)
        {
            if (mem.size == blk_size && mem.ptr == &_stack[N*(_cur_blk - 1)]) {
                _cur_blk--;

                NullPtrAllocator::deallocate(mem);
            }
        }

        Blk allocate(size_t size)
        {
            if (size != blk_size || _cur_blk == N) {
                return NullPtrAllocator::allocate(size);
            }

            return { &_stack[N*_cur_blk++], size };
        }

        bool owns(Blk& mem)
        {
            if (mem.size == blk_size &&_stack <= mem.ptr && mem.ptr < _stack + N*blk_size) {
                return true;
            }
            return false;
        }
};
