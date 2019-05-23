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

void mergeBeforeNode(Node *node, Node *ptr, size_t size)
{
    if (node->prev) {
        node->prev->next = ptr;
    } else {
        _root = ptr;
    }
    if (node->next) {
        node->next->prev = ptr;
    }
    ptr->prev = node->prev;
    ptr->next = node->next;
    ptr->size = node->size + size;
}

void
DoubleLinkedFreeList::insertNode(Node* ptr, size_t size)
{
    Node *iterator = _root;
    Node *tmp = nullptr;
    if (_root == nullptr) {
        _root = ptr;
        _root->prev = nullptr;
        _root->next = nullptr;
        _root->size = size;
        return;
    }
    do {
        if (iterator == ptr + size) {
            if (iterator->prev) {
                iterator->prev->next = ptr;
            } else {
                _root = ptr;
            }
            if (iterator->next) {
                iterator->next->prev = ptr;
            }
            ptr->prev = iterator->prev;
            ptr->next = iterator->next;
            ptr->size = iterator->size + size;
            return;
        }
        if (iterator + iterator.size == ptr) {
            iterator->size = iterator->size + size;
            return;
        }
        if (!tmp && iterator->size > ptr) {
            tmp = iterator;
        }
    } while (iterator->next != nullptr && iterator = iterator->next)
    // If we end up here that means we didn't merge regions
    if (tmp) {
        // We put region between others (sorted)
    } else {
        // We put region at the end
        iterator->next = ptr;
        ptr->prev = iterator;
        ptr->size = size;
        ptr->next = nullptr;
    }
}
