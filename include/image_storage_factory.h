#pragma once

#include <string>
#include <cstdint>
#include <vector>

#define FULLHD_HEIGHT   1920
#define FULLHD_WIDTH    1080

#define FRAME   2

#define DATA_HEIGHT FULLHD_HEIGHT + 2 * FRAME
#define DATA_WIDTH  FULLHD_WIDTH + 2 * FRAME

#define STORAGE_SIZE DATA_HEIGHT * DATA_WIDTH * 3

class ImageStorage
{
    friend class ImageStorageFactory;
    friend struct ImageStorageAllocator;

    private:
        uint32_t _height;
        uint32_t _width;
        uint8_t _frame;
        uint8_t** _data;

        ImageStorage(uint32_t height);
        
    public:
        uint32_t getHeight();
        uint32_t getWidth();
};


class ImageStorageFactory
{
    struct ImageStorageAllocator: std::allocator<ImageStorage>
    {
        template<class U, class... Args>
        void construct(U *u, Args&&... args)
        {
            new((void*)u) U(std::forward<Args>(args)...);
        }
        template<class U>
        struct rebind
        {
            typedef ImageStorageAllocator other;
        };
    };

    private:
        static uint8_t _pixel[STORAGE_SIZE];
        static uint32_t _used;
        std::vector<ImageStorage, ImageStorageAllocator> _warehouse;

        ImageStorageFactory() {}

        static ImageStorageFactory& getInstance();

    public:
        static ImageStorage& createImage(std::string filename);

        ImageStorageFactory(ImageStorageFactory const&) = delete;
        void operator=(ImageStorageFactory const&) = delete;
};
