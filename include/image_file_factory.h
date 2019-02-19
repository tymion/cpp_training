#pragma once
#include <string>
#include <cstdio>
#include <cstdbool>
#include <memory>
#include "image_file.h"
#include "color_space.h"

class ImageFileFactory
{
    private:
        static bool isPNG(FILE *file);

        ImageFileFactory() {}

    public:
        static ImageFile* openImageFile(std::string filename);
        static ImageFile* createImageFile(std::string filename, size_t width, size_t height, size_t color_depth, ColorSpace color);

        ImageFileFactory(ImageFileFactory const&) = delete;
        void operator=(ImageFileFactory const&) = delete;
};
