#pragma once

#include "mm/free_list.h"

template<size_t size>
class StackFreeList : public FreeList
{
    private:
        uint32_t data[size];

    public:
        StackFreeList() : FreeList(static_cast<void*>(data), size) {}
};
