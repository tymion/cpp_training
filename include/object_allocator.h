#pragma once

#include <allocator.h>
#include <fallback_allocator.h>
#include <free_list.h>
#include <stack_allocator.h>
#include <mallocator.h>

template<typename T, size_t N>
class ObjectAllocator
{
    FallbackAllocator<
        FreeList<
            StackAllocator<uint8_t, N, sizeof(T)>,
            sizeof(T)>,
        Mallocator> allocator;

    Blk mem;

    public:
    template<typename ...Args>
        T* allocate(Args&& ... args)
        {
            return new (allocator.allocate(sizeof(T)).ptr) T(args...);
        }

        void deallocate(T* ptr)
        {
            ptr->~T();
            mem.ptr = ptr;
            mem.size = sizeof(T);
            allocator.deallocate(mem);
        }
};
