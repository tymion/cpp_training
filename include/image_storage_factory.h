#pragma once

#include <cstdint>
#include <vector>
#include "image_file.h"
#include "storage.h"

#define FULLHD_HEIGHT   1920
#define FULLHD_WIDTH    1080

#define FRAME   2

#define DATA_HEIGHT (FULLHD_HEIGHT + 2 * FRAME)
#define DATA_WIDTH  (FULLHD_WIDTH + 2 * FRAME)

#define IMAGE_COMPONENT 4

#define STORAGE_SIZE DATA_HEIGHT * DATA_WIDTH * IMAGE_COMPONENT * 4

class ImageStorage : public Storage
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

        uint8_t* getRow(uint32_t index) {
            return _data[index];
        }
        uint8_t* operator[](uint32_t index) {
            return getRow(index);
        }
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
        static ImageStorage* createImageStorage(uint32_t height, uint32_t width);
        //static void fillStorageWithData(ImageStorage &storage, ImageFile &file);

        ImageStorageFactory(ImageStorageFactory const&) = delete;
        void operator=(ImageStorageFactory const&) = delete;
};
