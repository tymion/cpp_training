#pragma once

class DoubleLinkedFreeList
{
    struct Node {
        Node * next;
        Node * prev;
        size_t size;
    } *_root = nullptr;

    public:
        Node * getNode(size_t size);

        void insertNode(Node* ptr, size_t size);
};
