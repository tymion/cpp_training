#include <sys/stat.h>
#include <stdexcept>
#include <cstring>
#include <iostream>
#include "image_factory.h"
#include "libpng_wrapper.h"

#define PNG_HEADER_SIZE 8
char PNG_HEADER[PNG_HEADER_SIZE] = {'\211', 'P', 'N', 'G', '\r', '\n', '\032', '\n'};

bool ImageFactory::isPNG(FILE *file) {
    if (ftell(file) != 0) {
        fseek (file, 0, SEEK_SET); 
    }
    char header[PNG_HEADER_SIZE];
    int ret = fread(header, sizeof(char), PNG_HEADER_SIZE, file);

    if (ret == 0) {
        throw std::invalid_argument("Can't read file header.");
    }
    ret = memcmp(header, PNG_HEADER, PNG_HEADER_SIZE*sizeof(char));
    if (ret != 0) {
        return false;
    }
    fseek (file, 0, SEEK_SET);
    return true;
}

IImage* ImageFactory::createImage(std::string filename) {
    struct stat stbuf;
    lstat(filename.c_str(), &stbuf);
    if (!S_ISREG(stbuf.st_mode)) {
        throw std::invalid_argument("Invalid parameter. Pass picture file name.");
    }
    FILE *file = fopen(filename.c_str(), "rb");
    if (!file) {
        throw std::invalid_argument("Can't open file.");
    }
    IImage *image = NULL;
    if (isPNG(file)) {
        image = (IImage*) new PNGFileWrapper(file);
        std::cout << "Width: " << image->getWidth() << std::endl;
        std::cout << "Height: " << image->getHeight() << std::endl;
    }
    return image;
}
