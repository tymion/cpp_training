#pragma once

#include <string>
#include <cstdint>
#include <vector>
#include <memory>

#include "config.h"
#include "color_space.h"
#include "image.h"
#include "image_allocator.h"

class ImageFactory
{
    private:
        ImageFactory() {}

        static ImageAllocator alloc;
        static ImageFactory& getInstance();
        static ImageSharedPtr createImage(uint32_t height, uint32_t width, uint8_t frame, uint8_t component);
        static ColorSpace getColorSpaceFromComponent(size_t component);

    public:
        static ImageSharedPtr createImageFromFile(std::string fileName);
        static ImageSharedPtr createImageFromImage(ImageSharedPtr const img, ColorSpace color);
        static ImageSharedPtr createImageFromImage(ImageSharedPtr const img);
        static bool createFileFromImage(std::string name, ImageSharedPtr const img);

        ImageFactory(ImageFactory const&) = delete;
        void operator=(ImageFactory const&) = delete;
};
