#pragma once
#include <string>
#include <cstdio>
#include <cstdbool>
#include "iimage.h"

class Loader
{
    private:
        static bool isPNG(FILE *file);

        Loader() {}

    public:
        static IImage *loadImage(std::string filename);
//        static IImage *loadImage(std::string filename);

        Loader(Loader const&) = delete;
        void operator=(Loader const&) = delete;
};
