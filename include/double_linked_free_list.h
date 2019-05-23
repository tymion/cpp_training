#pragma once

#include <cstddef>

typedef struct Node_ Node;

struct Node_ {
    Node * next;
    Node * prev;
    size_t size;
};

class DoubleLinkedFreeList
{

    private:
        Node *_root = nullptr;
        Node *_last = nullptr;
        void beforeNode(Node *node, Node *ptr);
        void insertBeforeNode(Node *node, Node *ptr);
        void insertNodeAfterLast(Node* last, Node* ptr);
        void insertNodeAsRoot(Node* ptr);
        void mergeBeforeNode(Node *node, Node *ptr);

    public:
        void* findRegion(size_t size);
        void insertRegion(void* ptr, size_t size);

        Node * removeNode(size_t size);
        void insertNode(Node* ptr);
        void insertNodeWithMerge(Node* ptr);
};
