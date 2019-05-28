#include "double_linked_region_list.h"

Node *
DoubleLinkedRegionList::removeNode(size_t size)
{
    Node *tmp = _root;
    while (tmp != nullptr) {
        if (tmp->size >= size) {
            if (tmp->prev) {
                tmp->prev->next = tmp->next;
            }
            if (tmp->next) {
                tmp->next->prev = tmp->prev;
            }
            return tmp;
        }
        tmp = tmp->next;
    }
    return tmp;
}

void *
DoubleLinkedRegionList::findRegion(size_t size)
{
    Node *tmp = removeNode(size);
    if (tmp == nullptr) {
        return nullptr;
    }
    if (tmp->size > size) {
        (tmp + size)->size = tmp->size - size;
        insertNode(tmp + size);
    }
    tmp->size = size;
    return tmp;
}

inline void
DoubleLinkedRegionList::beforeNode(Node *node, Node *ptr)
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
}

inline void
DoubleLinkedRegionList::insertBeforeNode(Node *node, Node *ptr)
{
    beforeNode(node, ptr);
    ptr->next = node;
}

inline void
DoubleLinkedRegionList::mergeBeforeNode(Node *node, Node *ptr)
{
    beforeNode(node, ptr);
    ptr->next = node->next;
    ptr->size += node->size;
}

inline void
DoubleLinkedRegionList::insertNodeAfterLast(Node* ptr)
{
    _last->next = ptr;
    ptr->prev = _last;
    ptr->next = nullptr;
    _last = ptr;
}

inline void
DoubleLinkedRegionList::insertNodeAsRoot(Node* ptr)
{
    _root = ptr;
    _root->prev = nullptr;
    _root->next = nullptr;
    _last = _root;
}

void
DoubleLinkedRegionList::insertRegion(void* ptr, size_t size)
{
    ((Node*) ptr)->size = size;
    insertNode((Node*) ptr);
}

void
DoubleLinkedRegionList::insertNode(Node* ptr)
{
    Node *iterator = _root;
    if (_root == nullptr) {
        insertNodeAsRoot(ptr);
        return;
    }
    do {
        if (iterator->size > ptr->size) {
            insertBeforeNode(iterator, ptr);
        }
	iterator = iterator->next;
    } while (iterator != nullptr);
    // If we end up here that means we didn't insert ptr
    // We put region at the end
    insertNodeAfterLast(ptr);
}

void
DoubleLinkedRegionList::insertNodeWithMerge(Node* ptr)
{
    Node *iterator = _root;
    Node *tmp = nullptr;
    if (_root == nullptr) {
        insertNodeAsRoot(ptr);
        return;
    }
    do {
        if (iterator == ptr + ptr->size) {
            mergeBeforeNode(iterator, ptr);
            return;
        }
        if (iterator + iterator->size == ptr) {
            iterator->size = iterator->size + ptr->size;
            return;
        }
        if (!tmp && iterator->size > ptr->size) {
            tmp = iterator;
        }
	iterator = iterator->next;
    } while (iterator != nullptr);
    // If we end up here that means we didn't merge regions
    if (tmp) {
        // We put region between others (sorted)
        insertBeforeNode(tmp, ptr);
    } else {
        // We put region at the end
        insertNodeAfterLast(ptr);
    }
}
