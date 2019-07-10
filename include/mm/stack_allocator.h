#pragma once

#include <mm/allocator.h>
#include <mm/fixed_size_allocator.h>
#include <mm/nullptr_allocator.h>
#include "logger.h"

template<size_t blk_size, size_t N>
class StackAllocator : NullPtrAllocator
{
    uint8_t _stack[N*blk_size];
    size_t _cur_blk = 0;

    private:
        inline bool _deallocate(void* ptr)
        {
            if (ptr == &_stack[blk_size*(_cur_blk - 1)]) {
                _cur_blk--;
                return true;
            }
            return false;
        }

        inline bool _owns(void* ptr)
        {
            LOG_ALLOC("Stack allocator owns: mem.ptr=%p (_stack=%p|end_of_stack:%p)\n",
                        ptr, _stack, _stack + N*blk_size);
            if (_stack <= ptr && ptr < _stack + N*blk_size) {
                return true;
            }
            return false;
        }

    public:
        bool deallocate(void* ptr)
        {
            return _deallocate(ptr);
        }

        void deallocate(Blk& mem)
        {
            if (mem.size == blk_size && _deallocate(mem.ptr)) {
                mem.ptr = nullptr;
                mem.size = 0;
            }
        }

        Blk allocate(size_t size)
        {
            if (size != blk_size || _cur_blk >= N) {
                return NullPtrAllocator::allocate(size);
            }

            return { &_stack[blk_size*_cur_blk++], size };
        }

        void* allocate()
        {
            if (_cur_blk >= N) {
                return NullPtrAllocator::allocate();
            }

            return &_stack[blk_size*_cur_blk++];
        }

        bool owns(Blk& mem)
        {
            LOG_ALLOC("Stack allocator owns: mem.size=0x%lx (blk_size=0x%lx)\n",
                        mem.size, blk_size);
            if (mem.size == blk_size && _owns(mem.ptr)) {
                return true;
            }
            return false;
        }

        bool owns(void* ptr)
        {
            return _owns(ptr);
        }
};
