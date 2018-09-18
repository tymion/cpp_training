#include <sys/stat.h>
#include "libpng_wrapper.h"
#include <stdexcept>
#include <cstring>
#include <iostream>

#define PNG_HEADER_SIZE 8

PNGFileWrapper::PNGFileWrapper(FILE *file) {
    if (file == NULL) {
        throw std::invalid_argument("Invalid file descriptor.");
    }
    _file = file;
    _png = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    _info = png_create_info_struct(_png);
    setjmp(png_jmpbuf(_png));
    png_init_io(_png, file);
    png_read_info(_png, _info);
    _width = png_get_image_width(_png, _info);
    _height = png_get_image_height(_png, _info);
    png_byte color_type = png_get_color_type(_png, _info);
    png_byte bit_depth = png_get_bit_depth(_png, _info);
    if (bit_depth == 16) {
        png_set_strip_16(_png);
    }

    if (color_type == PNG_COLOR_TYPE_PALETTE) {
        png_set_palette_to_rgb(_png);
    }
    if (color_type == PNG_COLOR_TYPE_GRAY && bit_depth < 8) {
        png_set_expand_gray_1_2_4_to_8(_png);
    }
    if (png_get_valid(_png, _info, PNG_INFO_tRNS)) {
        png_set_tRNS_to_alpha(_png);
    }
    if (color_type == PNG_COLOR_TYPE_RGB ||
        color_type == PNG_COLOR_TYPE_GRAY ||
        color_type == PNG_COLOR_TYPE_PALETTE)
        png_set_filler(_png, 0xFF, PNG_FILLER_AFTER);

    if (color_type == PNG_COLOR_TYPE_GRAY ||
        color_type == PNG_COLOR_TYPE_GRAY_ALPHA)
        png_set_gray_to_rgb(_png);

    png_read_update_info(_png, _info);
}

PNGFileWrapper::~PNGFileWrapper() {
    fclose(_file);
}

uint32_t PNGFileWrapper::getWidth() {
    return _width;
}

uint32_t PNGFileWrapper::getHeight() {
    return _height;
}

uint8_t PNGFileWrapper::getComponentCnt() {
    return 1;
}

uint8_t PNGFileWrapper::getComponentSize() {
    return 8;
}

uint32_t PNGFileWrapper::getData(uint8_t *data, uint32_t length) {
    return 0;
}
