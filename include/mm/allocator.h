#pragma once

#include <cstdint>
#include <cstddef>

struct Blk_ {
    void *ptr;
    size_t size;
};

typedef struct Blk_ Blk;

class Allocator {
    public:
        virtual void deallocate(Blk& mem) = 0;
        virtual Blk allocate(size_t size) = 0;
        virtual bool owns(Blk& mem) = 0;
};
