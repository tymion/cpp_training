#pragma once

#include "allocator.h"
#include "nullptr_allocator.h"

template<class A, size_t blk_size>
class FreeList : NullPtrAllocator {
    A _pool;
    struct Node { Node * next; } *_root = nullptr;

    public:
        void deallocate(Blk& mem)
        {
            if (mem.ptr == nullptr || mem.size != blk_size) {
                return;
            }
            _pool.deallocate(mem);
            if (mem.ptr == nullptr) {
                return;
            }
            auto tmp = _root;
            _root = (Node *) mem.ptr;
            _root->next = tmp;
            mem.ptr = nullptr;
        }

        Blk allocate(size_t size)
        {
            if (size != blk_size) {
                return NullPtrAllocator::allocate(size);
            }
            if (_root == nullptr) {
                return _pool.allocate(size);
            }
            auto tmp = _root;
            _root = _root->next;
            return { tmp, size };
        }

        bool owns(Blk& mem)
        {
            return mem.size == blk_size && _pool.owns(mem);
        }
};
