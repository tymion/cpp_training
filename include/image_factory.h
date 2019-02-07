#pragma once

#include <string>
#include <cstdint>
#include <vector>

#include "config.h"
#include "color_space.h"

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
        ~Image();

    public:
        uint32_t getHeight() const;
        uint32_t getWidth() const;
        uint8_t getFrame() const;
        uint8_t getComponent() const;

        uint8_t* operator[](uint32_t index) const;
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
        static Image& createImage(auto height, auto width, auto frame, auto component);
        static void assignStorage(Image& img, auto height, auto width);

    public:
        static Image& createImageFromFile(std::string fileName);
        static Image& createImageFromImage(Image const& img, ColorSpace color);
        static Image& createImageFromImage(Image const& img);

        ImageFactory(ImageFactory const&) = delete;
        void operator=(ImageFactory const&) = delete;
};
