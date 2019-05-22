#pragma once

#include "allocator.h"
#include "nullptr_allocator.h"

class FreeList : NullPtrAllocator {
    A _pool;
    struct Node {
        Node * next;
        Node * prev;
        size_t size;
    } *_root = nullptr;

    private:
        Node * getNode(size_t size) {
            Node *tmp = _root;
            while (tmp != nullptr) {
                if (tmp.size >= size) {
                    return tmp;
                }
                tmp = tmp->next;
            }
            return tmp;
        }

        void insertNode(Blk& mem) {
            Node *iterator = _root;
            Node *tmp = _root;
            if (_root == NULL) {
                _root = (Node *) mem.ptr;
                _root->prev = nullptr;
                _root->next = nullptr;
                _root->size = mem.size;
                return;
            }
            do {
                if (iterator == mem.ptr + mem.size) {
                    Node *ltmp = (Node *) mem.ptr;
                    if (iterator->prev) {
                        iterator->prev->next = ltmp;
                    } else {
                        _root = ltmp;
                    }
                    if (iterator->next) {
                        iterator->next->prev = ltmp;
                    }
                    ltmp->prev = iterator->prev;
                    ltmp->next = iterator->next;
                    ltmp->size = iterator->size + mem.size;
                    return;
                }
                if (iterator + iterator.size == mem.ptr) {
                    iterator->size = iterator->size + mem.size;
                    return;
                }
                if (!tmp && iterator->size > mem.ptr) {
                    tmp = iterator;
                }
            } while (iterator->next != NULL && iterator = iterator->next)
            // If we end up here that means we didn't merge regions
            if (tmp) {
                // We put region between others (sorted)
                Node *ltmp = (Node *) mem.ptr;
                if (tmp->prev) {
                    tmp->prev->next = ltmp;
                } else {
                    _root = ltmp;
                }
                if (tmp->next) {
                    tmp->next->prev = ltmp;
                }
                ltmp->prev = tmp->prev;
                ltmp->next = tmp->next;
                ltmp->size = tmp->size + mem.size;
            } else {
                // We put region at the end
                
            }
        }

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
