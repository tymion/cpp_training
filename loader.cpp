#include <sys/stat.h>
#include "loader.hpp"
#include <stdexcept>
#include <cstring>
#include <iostream>

#define PNG_HEADER_SIZE 8
char PNG_HEADER[8] = {'\211', 'P', 'N', 'G', '\r', '\n', '\032', '\n'};

bool Loader::isPNG() {
    if (ftell(file) != 0) {
        fseek (file, 0, SEEK_SET); 
    }
    char header[PNG_HEADER_SIZE];
    int ret = fread(header, sizeof(char), PNG_HEADER_SIZE, file);

    if (ret == 0) {
        throw std::invalid_argument("Can't read file header.");
    }
    ret = memcmp(header, PNG_HEADER, PNG_HEADER_SIZE*sizeof(char));
    if (ret == 0) {
        return true;
    }
    return false;
}

PNGChunkType Loader::readChunkHeaderD(int &length) {
    char chunk_header[8];
    int ret = fread(chunk_header, sizeof(char), 8, file);

    if (ret == 0) {
        throw std::invalid_argument("Can't read file chunk header.");
    }
    cout << "Chunk data length:" << (int) chunk_header[0] << endl;
    length = chunk_header[0];
    return (PNGChunkType) 0;
}

PNGChunkType Loader::readChunkHeader(int &length) {
    unsigned int chunk_header[2];
    int ret = fread(chunk_header, sizeof(unsigned int), 2, file);

    if (ret == 0) {
        throw std::invalid_argument("Can't read file chunk header.");
    }
    cout << "Chunk data length:" << chunk_header[0] << endl;
    length = chunk_header[0];
    cout << "Chunk Type:" << chunk_header[1] << endl;
    int bit = 0;
    if (((chunk_header[1] > 5) & 1) == 1) {
        bit |= PNGChunkType::Ancillary;
        cout << "Ancillary:" << 1 << endl;
    }
    if (((chunk_header[1] > 13) & 1) == 1) {
        bit |= PNGChunkType::Private;
        cout << "Private:" << 1 << endl;
    }
    if (((chunk_header[1] > 21) & 1) == 1) {
        bit |= PNGChunkType::Reserved;
        cout << "Reserved:" << 1 << endl;
    }
    if (((chunk_header[1] > 29) & 1) == 1) {
        bit |= PNGChunkType::SafeToCopy;
        cout << "Safe-to-copy:" << 1 << endl;
    }
    return (PNGChunkType) bit;
}

void Loader::readCrc() {
    int crc;
    int ret = fread(&crc, sizeof(int), 1, file);
    if (ret == 0) {
        throw std::invalid_argument("Can't read crc.");
    }

    cout << "CRC:" << crc << endl;
}

void Loader::readChunk(char (&data), const int &length) {
    int ret = fread(&data, sizeof(char), length, file);
    if (ret == 0) {
        throw std::invalid_argument("Can't read data.");
    }
}

Loader::Loader(string filename) {
    struct stat stbuf;
    lstat(filename.c_str(), &stbuf);
    if (!S_ISREG(stbuf.st_mode)) {
        throw std::invalid_argument("Invalid parameter. Pass picture file name.");
    }
    file = fopen(filename.c_str(), "rb");
    if (!isPNG()) {
        throw std::invalid_argument("Invalid parameter. File isn't PNG.");
    }
    int length;
    readChunkHeaderD(length);
    char *data = new char(length);
    readChunk(*data, length);
    readCrc();
    readChunkHeader(length);
}

void Loader::setRegion(int height, int width) {
    height = height;
    width = width;
}

int Loader::getData(char* data, size_t n) {
    int ret = fread(data, sizeof(char), n*sizeof(char), file);
    return ret;
}
