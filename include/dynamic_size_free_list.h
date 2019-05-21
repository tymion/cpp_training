#pragma once

#include "allocator.h"
#include "nullptr_allocator.h"

class FreeList : NullPtrAllocator {
    A _pool;
    struct Node { Node * next; } *_root = nullptr;

    private:

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
