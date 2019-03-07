#pragma once

#include <iostream>
#include <string>
#include <cstdint>
#include <vector>
#include <memory>

#include "image_allocator.h"
#include "config.h"
#include "color_space.h"

#define STORAGE_SIZE DATA_HEIGHT * DATA_WIDTH * IMAGE_COMPONENT * 4

class Image
{
    friend class ImageFactory;
    friend class ImageAllocator<Image>;
//    friend void destroy(ImageAllocator<Image>& alloc, Image *p);

    private:
        uint32_t _height = 0;
        uint32_t _width = 0;
        uint8_t _frame = 0;
        uint8_t _component = 0;
        uint8_t** _data = NULL;

        Image(uint32_t height);
        ~Image();

    public:
        uint32_t getHeight() const;
        uint32_t getWidth() const;
        uint8_t getFrame() const;
        uint8_t getComponent() const;
        void fillFrames();

        uint8_t* operator[](uint32_t index);
        uint8_t* operator[](uint32_t index) const;
};


class ImageFactory
{
    private:
        static uint8_t _pixel[STORAGE_SIZE];
        static uint32_t _used;
        std::vector<Image, ImageAllocator<Image>> _warehouse;

        ImageFactory() {}

        static ImageFactory& getInstance();
        static Image& createImage(auto height, auto width, auto frame, auto component);
        static void assignStorage(Image& img, auto height, auto width);
        static ColorSpace getColorSpaceFromComponent(size_t component);

    public:
        static Image& createImageFromFile(std::string fileName);
        static Image& createImageFromImage(Image const& img, ColorSpace color);
        static Image& createImageFromImage(Image const& img);
        static bool createFileFromImage(std::string name, Image const& img);

        ImageFactory(ImageFactory const&) = delete;
        void operator=(ImageFactory const&) = delete;
};
