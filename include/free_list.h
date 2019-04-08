#pragma once

#include "allocator.h"

template<class A, size_t blk_size>
class FreeList : Allocator {
    A _fallback;
    struct Node { Node * next; } *_root = nullptr;

    public:
        void deallocate(Blk& mem)
        {
            if (mem.ptr == nullptr || mem.size != blk_size) {
                return;
            }
            _fallback.deallocate(mem);
            if (mem.ptr == nullptr) {
                return;
            }
            auto tmp = _root;
            _root = (Node *) mem.ptr;
            _root.next = tmp;
        }

        Blk& allocate(size_t size)
        {
            if (size != blk_size || _root == nullptr) {
                return _fallback.allocate(size);
            }
            auto tmp = _root;
            _root = _root->next;
            return { _root, size };
        }

        bool owns(Blk& mem)
        {
            return mem.size == blk_size && _fallback.owns(mem);
        }
};
