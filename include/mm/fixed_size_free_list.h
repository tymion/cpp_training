#pragma once

#include "mm/allocator.h"
#include "mm/nullptr_allocator.h"

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
                return;
            }
            auto tmp = _root;
            _root = (Node *) mem.ptr;
            _root->next = tmp;
            mem.ptr = nullptr;
            mem.size = 0;
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
