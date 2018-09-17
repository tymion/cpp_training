#include <sys/stat.h>
#include "png.h"
#include <stdexcept>
#include <cstring>
#include <iostream>

#define PNG_HEADER_SIZE 8

PNGFile::PNGFile(FILE *file) {
    if (file == NULL) {
        throw std::invalid_argument("Invalid file descriptor.");
    }
    _file = file;
    _png = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    _info = png_create_info_struct(_png);
    setjmp(png_jmpbuf(png));
    png_init_io(_png, file);
    png_read_info(_png, _info);
    _width = png_get_image_width(_png, _info);
    _height = png_get_image_height(_png, _info);
    color_type = png_get_color_type(_png, _info);
    bit_depth = png_get_bit_depth(_png, _info);
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

PNGFile::~PNGFile() {
    fclose(_file);
}

uint32_t PNGFile::getWidth() {
    return _width;
}

uint32_t PNGFile::getHeight() {
    return _height;
}

uint8_t PNGFile::getComponentCnt() {
    switch (_type & 0xff00) {
        case Greyscale:
            return 1;
        case IndexedColor:
            return 3;
        case GreyscaleAlpha:
            return 2;
        case TrueColor:
            return 3;
        case TrueColorAlpha:
            return 4;
        default:
            return 1;
    }
}

uint8_t PNGFile::getComponentSize() {
    return _type & 0xff;
}

uint32_t PNGFile::getData(uint8_t *data, uint32_t length) {
    if (_state == PNGFileState::Closed) {
        return 0;
    }
    size_t ret = 0;
    size_t tmp = 0;
    uint32_t toRead = length;
    std::cout << "getData|toRead:" << toRead << std::endl;
    while (_state == PNGFileState::Data && ret != length) {
        std::cout << "getData" << std::endl;
        if (_dataLeft == 0) {
            readCrc();
            struct PNGChunk_ chunk;
            readChunkHeader(&chunk);
            if (_state == PNGFileState::Closed) {
                throw std::invalid_argument("getData Closed!!!!");
            }
        }
        if (toRead > _dataLeft) {
            toRead = _dataLeft;
        }
        tmp = readData(data, toRead);
        if (tmp == 0) {
            
            break;
        }
        ret += tmp;
        toRead = length - ret;
    }
    _dataLeft -= ret;
    return ret;
}
