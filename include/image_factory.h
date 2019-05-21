#pragma once

#include <string>
#include <cstdint>
#include <vector>
#include <memory>

#include "config.h"
#include "color_space.h"
#include "image.h"
#include "object_allocator.h"

using ImageSharedPtr = std::shared_ptr<Image>;

void ImageDeleter(Image* img);

using ImageAllocator = ObjectAllocator<Image, 10>;

class ImageFactory
{
    private:
        static uint32_t _used;
        static uint8_t _pixel[STORAGE_SIZE];
        static ImageAllocator _allocator;

        ImageFactory() {}

        static ImageFactory& getInstance();
        static Image& createImage(uint32_t height, uint32_t width, uint8_t frame, uint8_t component);
        static void assignStorage(Image& img, uint32_t height, uint32_t width);
        static ColorSpace getColorSpaceFromComponent(size_t component);
        static void assignStorage(Image& img, auto height, auto width);

    public:
        static Image& createImageFromFile(std::string fileName);
        static Image& createImageFromImage(Image const& img, ColorSpace color);
        static Image& createImageFromImage(Image const& img);
        static bool createFileFromImage(std::string name, Image const& img);
        static void deleteImage(Image* img);

        ImageFactory(ImageFactory const&) = delete;
        void operator=(ImageFactory const&) = delete;
};
