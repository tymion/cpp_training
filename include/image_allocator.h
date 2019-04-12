#pragma once

#include <allocator.h>
#include <fallback_allocator.h>
#include <free_list.h>
#include <stack_allocator.h>
#include <mallocator.h>

template<typename T, size_t N>
class ImageAllocator
{
    FallbackAllocator<
        FreeList<
            StackAllocator<uint8_t, N, sizeof(T)>,
            sizeof(T)>,
        Mallocator> allocator;
    public:
    template<class ...Args>
        void* allocate(Args... args)
        {
            return new (allocator.allocate(sizeof(T)).ptr) T(args);
        }

        void deallocate(void* ptr)
        {
            allocator.deallocate({ ptr, sizeof(T)});
        }
};
