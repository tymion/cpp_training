#include <sys/stat.h>
#include <stdexcept>
#include <cstring>
#include <iostream>
#include "libpng_wrapper.h"
#include "logger.h"

png_byte PNGFileWrapper::ColorSpaceToLibPNG(ColorSpace color)
{
    switch (color) {
        case ColorSpace::Grayscale:
            return PNG_COLOR_TYPE_GRAY;
        case ColorSpace::IndexedColor:
            return PNG_COLOR_TYPE_PALETTE;
        case ColorSpace::GrayscaleAlpha:
            return PNG_COLOR_TYPE_GRAY_ALPHA;
        case ColorSpace::TrueColor:
            return PNG_COLOR_TYPE_RGB;
        case ColorSpace::TrueColorAlpha:
            return PNG_COLOR_TYPE_RGB_ALPHA;
        default:
            return 0;
    }
}

PNGFileWrapper::PNGFileWrapper(FILE *file, size_t width, size_t height,
                                size_t color_depth, ColorSpace color) {
    if (file == NULL) {
        throw std::invalid_argument("Invalid file descriptor.");
    }
    _file = file;
    _png = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    _info = png_create_info_struct(_png);
    setjmp(png_jmpbuf(_png));
    png_init_io(_png, file);
    png_byte png_color = ColorSpaceToLibPNG(color);
    png_set_IHDR(_png, _info, width, height, color_depth, png_color,
                    PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_DEFAULT,
                    PNG_FILTER_TYPE_DEFAULT);
    png_write_info(_png, _info);
    _width = width;
    _height = height;
    _bit_depth = color_depth;
    if (png_color == PNG_COLOR_TYPE_GRAY ||
            png_color == PNG_COLOR_TYPE_GRAY_ALPHA) {
        png_set_gray_to_rgb(_png);
    }
    _row_pointers = (png_bytepp)png_malloc(_png, sizeof(png_bytepp) * height);
}

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
    png_byte color_type = png_get_color_type(_png, _info);
    _bit_depth = png_get_bit_depth(_png, _info);
    _width = png_get_image_width(_png, _info);
    _height = png_get_image_height(_png, _info);

    if (_bit_depth == 16) {
        png_set_strip_16(_png);
    }

    if (color_type == PNG_COLOR_TYPE_PALETTE) {
        png_set_palette_to_rgb(_png);
    }
    if (color_type == PNG_COLOR_TYPE_GRAY && _bit_depth < 8) {
        png_set_expand_gray_1_2_4_to_8(_png);
    }
    if (color_type == PNG_COLOR_TYPE_GRAY ||
        color_type == PNG_COLOR_TYPE_GRAY_ALPHA)
        png_set_gray_to_rgb(_png);

    png_read_update_info(_png, _info);

    _row_pointers = (png_bytepp)png_malloc(_png, sizeof(png_bytepp) * _height);
    _read = true;
}

PNGFileWrapper::~PNGFileWrapper() {
    free(_row_pointers);
    if (_read) {
        png_destroy_read_struct(&_png, &_info, NULL);
    } else {
        png_destroy_write_struct(&_png, &_info);
    }
    fclose(_file);
}

uint32_t PNGFileWrapper::getWidth() {
    return _width;
}

uint32_t PNGFileWrapper::getHeight() {
    return _height;
}

uint8_t PNGFileWrapper::getComponentCnt() {
    return png_get_rowbytes(_png, _info) / _width;
}

uint8_t PNGFileWrapper::getComponentSize() {
    return _bit_depth;
}

bool PNGFileWrapper::loadImage(std::function<uint8_t* (uint32_t)> callback) {
    for (uint32_t y = 0; y < _height; y++) {
        _row_pointers[y] = (png_byte*)callback(y);
        if (!_row_pointers[y]) {
            LOG("row_pointers[%d] is null\n", y);
            return false;
        }
    }

    png_read_image(_png, _row_pointers);
    png_read_end(_png, NULL);

    return true;
}

bool PNGFileWrapper::saveImage(std::function<uint8_t* (uint32_t)> callback) {
    for (uint32_t y = 0; y < _height; y++) {
        _row_pointers[y] = (png_byte*)callback(y);
        if (!_row_pointers[y]) {
            return false;
        }
    }

    png_write_image(_png, _row_pointers);
    png_write_end(_png, NULL);

    return true;
}
