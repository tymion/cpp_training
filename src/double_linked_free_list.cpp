#include "double_linked_free_list.h"

Node *
DoubleLinkedFreeList::getNode(size_t size)
{
    Node *tmp = _root;
    while (tmp != nullptr) {
        if (tmp.size >= size) {
            return tmp;
        }
        tmp = tmp->next;
    }
    return tmp;
}

void
DoubleLinkedFreeList::insertBlk(Blk& mem)
{
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
        Node *ltmp = (Node *) mem.ptr;
        iterator->next = ltmp;
        ltmp->prev = iterator;
        ltmp->size = mem.size;
        ltmp->next = nullptr;
    }
}
