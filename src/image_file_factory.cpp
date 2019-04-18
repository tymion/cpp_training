#include <sys/stat.h>
#include <stdexcept>
#include <cstring>
#include <iostream>
#include "image_file_factory.h"
#include "libpng_wrapper.h"
#include "logger.h"

#define PNG_HEADER_SIZE 8
char PNG_HEADER[PNG_HEADER_SIZE] = {'\211', 'P', 'N', 'G', '\r', '\n', '\032', '\n'};

bool ImageFileFactory::isPNG(FILE *file) {
    if (ftell(file) != 0) {
        fseek (file, 0, SEEK_SET); 
    }
    uint8_t header[PNG_HEADER_SIZE];
    if (fread(header, sizeof(uint8_t), PNG_HEADER_SIZE, file) == 0) {
        throw std::invalid_argument("Can't read file header.");
    }
    if (png_sig_cmp(header, 0, PNG_HEADER_SIZE) != 0) {
        return false;
    }
    fseek (file, 0, SEEK_SET);
    return true;
}

ImageFile* ImageFileFactory::openImageFile(std::string filename) {
    struct stat stbuf;
    if (lstat(filename.c_str(), &stbuf) != 0) {
        throw std::invalid_argument("File not found");
    }
    if (!S_ISREG(stbuf.st_mode)) {
        throw std::invalid_argument("Invalid parameter. Pass picture file name.");
    }
    FILE *file = fopen(filename.c_str(), "rb");
    if (!file) {
        throw std::invalid_argument("Can't open file.");
    }
    ImageFile *image = NULL;
    if (isPNG(file)) {
        image = new PNGFileWrapper(file);
        if (image) {
            LOG("Width:%d\n", image->getWidth());
            LOG("Height:%d\n", image->getHeight());
        }
    }
    return image;
}

ImageFile* ImageFileFactory::createImageFile(std::string filename, size_t width, size_t height,
                                            size_t color_depth, ColorSpace color) {
    struct stat stbuf;
    if (lstat(filename.c_str(), &stbuf) == -1 && errno != ENOENT) {
        throw std::invalid_argument("File already exists.");
    }
    FILE *file = fopen(filename.c_str(), "wb");
    if (!file) {
        throw std::invalid_argument("Can't create file.");
    }
    return new PNGFileWrapper(file, width, height, color_depth, color);
}
