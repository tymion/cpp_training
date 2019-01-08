#pragma once
#include <string>
#include <cstdio>
#include <cstdbool>
#include "iimage.h"

class ImageFactory
{
    private:
        static bool isPNG(FILE *file);

        ImageFactory() {}

    public:
        static IImage *createImage(std::string filename);

        ImageFactory(ImageFactory const&) = delete;
        void operator=(ImageFactory const&) = delete;
};
