#include <sys/stat.h>
#include "loader.h"
#include <stdexcept>
#include <cstring>
#include <iostream>
#include "pngfile.h"

#define PNG_HEADER_SIZE 8
char PNG_HEADER[PNG_HEADER_SIZE] = {'\211', 'P', 'N', 'G', '\r', '\n', '\032', '\n'};

bool Loader::isPNG(FILE *file) {
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

IImage* Loader::loadImage(string filename) {
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
        image = new PNGFile(file);
        cout << "Width: " << image->getWidth() << endl;
        cout << "Height: " << image->getHeight() << endl;
    }
    return image;
}
