#pragma once
#include <cstdio>
#include <cstdbool>
#include <cstdint>
#include <png.h>
#include "image_file.h"
#include "color_space.h"

class PNGFileWrapper: public ImageFile
{
    private:
        FILE *_file = NULL;
        png_structp _png;
        png_infop _info;
        png_byte _bit_depth;
        png_bytep *_row_pointers;
        png_uint_32 _height = 0;
        png_uint_32 _width = 0;
        bool _read = false;

        png_byte ColorSpaceToLibPNG(ColorSpace color);

    public:
        PNGFileWrapper(FILE *file);
        PNGFileWrapper(FILE *file, size_t width, size_t height, size_t color_depth,
                        ColorSpace color);
        ~PNGFileWrapper();
        uint32_t getHeight();
        uint32_t getWidth();
        bool loadImage(std::function<uint8_t* (uint32_t)> callback);
        bool saveImage(std::function<uint8_t* (uint32_t)> callback);
        uint8_t getComponentSize();
        uint8_t getComponentCnt();
};
