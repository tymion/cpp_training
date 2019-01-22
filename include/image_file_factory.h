#pragma once
#include <string>
#include <cstdio>
#include <cstdbool>
#include <memory>
#include "image_file.h"

class ImageFileFactory
{
    private:
        static bool isPNG(FILE *file);

        ImageFileFactory() {}

    public:
        static ImageFile* createImageFile(std::string filename);

        ImageFileFactory(ImageFileFactory const&) = delete;
        void operator=(ImageFileFactory const&) = delete;
};
