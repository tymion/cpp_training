#pragma once

#include <cstddef>
#include <cstdint>

class FixedSizeAllocator {
    public:
        virtual bool deallocate(void* ptr) = 0;
        virtual void* allocate() = 0;
        virtual bool owns(void* ptr) = 0;
};
