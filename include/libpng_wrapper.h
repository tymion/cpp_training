#pragma once
#include <cstdio>
#include <cstdbool>
#include <cstdint>
#include <png.h>
#include "iimage.h"

class PNGFileWrapper: public IImage {
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
        bool getData(uint32_t row, uint8_t **data);
        uint8_t getComponentSize();
        uint8_t getComponentCnt();
};
