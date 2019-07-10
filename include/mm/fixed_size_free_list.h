#pragma once

#include "mm/allocator.h"
#include "mm/fixed_size_allocator.h"
#include "mm/nullptr_allocator.h"
#include "logger.h"

template<class A, size_t blk_size>
class FixedSizeFreeList : NullPtrAllocator
{
    private:
        A _pool;
        struct Node { Node * next; } *_root = nullptr;

    public:
        void deallocate(Blk& mem)
        {
            if (!owns(mem)) {
                return;
            }
            _pool.deallocate(mem);
            if (mem.ptr == nullptr) {
                LOG_ALLOC("Deallocating from pool failed.\n");
                return;
            }
            LOG_ALLOC("Deallocating will supply a free list.\n");
            auto tmp = _root;
            _root = (Node *) mem.ptr;
            _root->next = tmp;
            mem.ptr = nullptr;
            mem.size = 0;
        }

        bool deallocate(void* ptr)
        {
            if (!owns(ptr)) {
                return false;
            }
            if (_pool.deallocate(ptr)) {
                return true;
            }
            auto tmp = _root;
            _root = (Node *) ptr;
            _root->next = tmp;
            return true;
        }

        Blk allocate(size_t size)
        {
            if (size != blk_size) {
                return NullPtrAllocator::allocate(size);
            }
            if (_root == nullptr) {
                LOG_ALLOC("Allocating from pool.\n");
                return _pool.allocate(size);
            }
            LOG_ALLOC("Allocating from free list.\n");
            auto tmp = _root;
            _root = _root->next;
            return { tmp, size };
        }

        void* allocate()
        {
            if (_root == nullptr) {
                LOG_ALLOC("Allocating from pool.\n");
                return _pool.allocate();
            }
            LOG_ALLOC("Allocating from free list.\n");
            auto tmp = _root;
            _root = _root->next;
            return tmp;
        }

        bool owns(Blk& mem)
        {
            LOG_ALLOC("Owns(Blk):%s\n",
                        (mem.size == blk_size && _pool.owns(mem)) ? "true" : "false");
            return mem.size == blk_size && _pool.owns(mem);
        }

        bool owns(void* ptr)
        {
            LOG_ALLOC("Owns(void*):%s\n", _pool.owns(ptr) ? "true" : "false");
            return _pool.owns(ptr);
        }
};
