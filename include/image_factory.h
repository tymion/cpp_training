#pragma once

#include <string>
#include <cstdint>
#include <vector>
#include <memory>

#include "config.h"
#include "color_space.h"
#include "object_allocator.h"

#define STORAGE_SIZE DATA_HEIGHT * DATA_WIDTH * IMAGE_COMPONENT * 4
#define IMAGE_ALLOCATOR_POOL_SIZE 10

class Image;

using ImageAllocator = ObjectAllocator<Image, IMAGE_ALLOCATOR_POOL_SIZE>;

class Image
{
    friend class ImageFactory;
    friend ImageAllocator;

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

using ImageSharedPtr = std::shared_ptr<Image>;

void ImageDeleter(Image* img);

class ImageFactory
{
    private:

        static ImageAllocator _allocator;
        static uint8_t _pixel[STORAGE_SIZE];
        static uint32_t _used;

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
        static void deleteImage(Image* img);

        ImageFactory(ImageFactory const&) = delete;
        void operator=(ImageFactory const&) = delete;
};
