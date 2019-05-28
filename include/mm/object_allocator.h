#pragma once

#include <mm/allocator.h>
#include <mm/fallback_allocator.h>
#include <mm/fixed_size_free_list.h>
#include <mm/stack_allocator.h>
#include <mm/mallocator.h>

template<typename T, size_t N>
class ObjectAllocator
{
    FallbackAllocator<
        FixedSizeFreeList<
            StackAllocator<N, sizeof(T)>,
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
