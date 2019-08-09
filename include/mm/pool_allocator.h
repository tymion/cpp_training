#pragma once

#include <mm/allocator.h>
#include <mm/fixed_size_allocator.h>
#include <logger.h>

template<class B, class E, size_t N>
class PoolAllocator
{
    private:
        B base_pool;
        Allocator *alloc[N];
        size_t idx = 0;
        size_t pool_size = 1;

    public:
        PoolAllocator()
        {
            alloc[0] = &base_pool;
        }

        void* allocate()
        {
            void* ptr = alloc[idx]->allocate();
            if (ptr) {
                return ptr;
            }
            idx++;
            if (idx >= pool_size) {
                if (idx >= N) {
                    LOG_ALLOC("Exceeded size of pool table (N=%lu).", N);
                    return NullPtrAllocator::allocate();
                }
                alloc[idx] = new E();
                if (alloc[idx] == nullptr) {
                    LOG_ALLOC("Allocating another pool has failed.");
                    return NullPtrAllocator::allocate();
                }
                pool_size++;
            }
            return alloc[idx]->allocate();
        }

        bool deallocate(void* ptr)
        {

        }
};
