#pragma once
#include <cstdio>
#include <cstdbool>
#include <cstdint>
#include <png.h>
#include "image_file.h"

class PNGFileWrapper: public ImageFile
{
    private:
        FILE *_file;
        png_structp _png;
        png_infop _info;
        png_byte _bit_depth;
        png_bytep *_row_pointers;
        uint32_t _height;
        uint32_t _width;

    public:
        PNGFileWrapper(FILE *newfile);
        ~PNGFileWrapper();
        uint32_t getHeight();
        uint32_t getWidth();
        bool loadImage(std::function<uint32_t* (uint32_t)> callback);
        uint8_t getComponentSize();
        uint8_t getComponentCnt();
};
