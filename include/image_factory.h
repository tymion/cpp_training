#pragma once

#include <string>
#include <cstdint>
#include <vector>

#include "config.h"

#define STORAGE_SIZE DATA_HEIGHT * DATA_WIDTH * IMAGE_COMPONENT * 4

class Image
{
    friend class ImageFactory;
    friend struct ImageAllocator;

    private:
        uint32_t _height;
        uint32_t _width;
        uint8_t _frame;
        uint8_t _component;
        uint8_t** _data;

        Image(uint32_t height);

    public:
        uint32_t getHeight();
        uint32_t getWidth();
        uint8_t getFrame();

        uint8_t* operator[](uint32_t index);
};


class ImageFactory
{
    struct ImageAllocator: std::allocator<Image>
    {
        template<class U, class... Args>
        void construct(U *u, Args&&... args)
        {
            new((void*)u) U(std::forward<Args>(args)...);
        }
        template<class U>
        struct rebind
        {
            typedef ImageAllocator other;
        };
    };

    private:
        static uint8_t _pixel[STORAGE_SIZE];
        static uint32_t _used;
        std::vector<Image, ImageAllocator> _warehouse;

        ImageFactory() {}

        static ImageFactory& getInstance();

    public:
        static Image* createImage(uint32_t height, uint32_t width);
        static Image& createImageFromFile(std::string fileName);

        ImageFactory(ImageFactory const&) = delete;
        void operator=(ImageFactory const&) = delete;
};
