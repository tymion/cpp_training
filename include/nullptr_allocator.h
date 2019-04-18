#pragma once

class NullPtrAllocator : Allocator {
    public:
        void deallocate(Blk& mem)
        {
            if (mem.ptr == nullptr) {
                mem.size = 0;
            }
        }

        Blk allocate(size_t size)
        {
            return { nullptr, 0 };
        }

        bool owns(Blk& mem)
        {
            if (mem.size == 0 && mem.ptr == nullptr) {
                return true;
            }
            return false;
        }
};
