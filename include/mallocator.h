#pragma once

#include <cstdlib>
#include <allocator.h>

class Mallocator : Allocator {
    public:
void
Mallocator::deallocate(Blk& mem)
{
    free(mem.ptr);
}

Blk&
Mallocator::allocate(size_t size)
{
    return { malloc(size), size };
}

bool
Mallocator::owns(Blk& mem)
{
    return true;
}
};
