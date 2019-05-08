#pragma once

#define POOL_SIZE 10

template<typename T, size_t N, size_t H, size_t W>
class ImageProcessorAllocator: ObjectAllocator<T, N>
{
    static FreeList<StackAllocator<N, H*sizeof(uint32_t*)>, H*sizeof(uint32_t*)> _tabAllocator;
    static FreeList<StackAllocator<N*H, W*sizeof(uint32_t*)>, W*sizeof(uint32_t)> _dataAllocator;

    public:
        ImageProcessor* allocate()
        {
            ImageProcessor* img = new (allocator.allocate(sizeof(ImageProcessor)).ptr) T();
            img->data = _tabAllocator.allocate(H*sizeof(uint32_t*)).ptr;
            for (auto i = 0; i < H; i++) {
                img._data[i] = _dataAllocator.allocate(W*sizeof(uint32_t*));
            }
        }
};
