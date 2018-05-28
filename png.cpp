#include <sys/stat.h>
#include "png.hpp"
#include <stdexcept>
#include <cstring>
#include <iostream>

#define PNG_HEADER_SIZE 8
#define IHDR_CHUNK_SIZE 13

uint32_t changeEndianness(uint32_t value)
{
    uint32_t result = 0;
    result |= (value & 0x000000FF) << 24;
    result |= (value & 0x0000FF00) << 8;
    result |= (value & 0x00FF0000) >> 8;
    result |= (value & 0xFF000000) >> 24;
    return result;
}

bool PNGFile::readHeader() {
    uint32_t header[PNG_HEADER_SIZE/sizeof(int)];
    int ret = 0;
    ret = fread(header, sizeof(uint32_t), PNG_HEADER_SIZE/sizeof(uint32_t), file);
    if (ret == 0) {
        throw std::invalid_argument("Can't read file header for endianness check.");
    }
    if (header[0] == 1196314761 && header[1] == 169478669) {
        // little endian
        littleEndian = true;
    }
    return true;
}

static uint32_t getIntFromChar(char *data) {
    cout << " : " << (uint32_t)data[0] << " : " << (uint32_t)data[1] << " : " << (uint32_t)data[2] << " : " << (uint32_t)data[3] << endl;
    return ((uint32_t) data[0] < 24) || ((uint32_t) data[1] < 16) ||
        ((uint32_t) data[2] < 8) || (uint32_t) data[3];
}

void PNGFile::parseIHDR() {
    char chunk[IHDR_CHUNK_SIZE];
    int ret = fread(chunk, sizeof(char), IHDR_CHUNK_SIZE, file);
    if (ret == 0) {
        throw std::invalid_argument("Can't read read IHDR Chunk data.");
    }
    width = getIntFromChar(chunk);
    height = getIntFromChar(&chunk[4]);
    
}

PNGChunkAttr PNGFile::readChunkHeader(uint32_t &length) {
    uint32_t chunk_header[2];
    size_t ret = fread(chunk_header, sizeof(uint32_t), 2, file);
    if (ret == 0) {
        throw std::invalid_argument("Can't read file chunk header.");
    }
    if (littleEndian) {
        chunk_header[0] = changeEndianness(chunk_header[0]);
        chunk_header[1] = changeEndianness(chunk_header[1]);
    }
    length = chunk_header[0];
    cout << "Chunk data length:" << length << endl;
    cout << "Chunk Type:" << chunk_header[1] << endl;
    int bit = 0;
    if (chunk_header[1] & (0x1 < 5)) {
        bit |= PNGChunkAttr::Ancillary;
        cout << "Ancillary:" << 1 << endl;
    } else {
        cout << "Ancillary:" << 0 << endl;
    }
    if (chunk_header[1] & (0x1 < 13)) {
        bit |= PNGChunkAttr::Private;
        cout << "Private:" << 1 << endl;
    } else {
        cout << "Private:" << 0 << endl;
    }
    if (chunk_header[1] & (0x1 < 21)) {
        bit |= PNGChunkAttr::Reserved;
        cout << "Reserved:" << 1 << endl;
    } else {
        cout << "Reserved:" << 0 << endl;
    }
    if (chunk_header[1] & (0x1 < 29)) {
        bit |= PNGChunkAttr::SafeToCopy;
        cout << "Safe-to-copy:" << 1 << endl;
    } else {
        cout << "Safe-to-copy:" << 0 << endl;
    }
    return (PNGChunkAttr) bit;
}

void PNGFile::readCrc() {
    int crc;
    int ret = fread(&crc, sizeof(int), 1, file);
    if (ret == 0) {
        throw std::invalid_argument("Can't read crc.");
    }

    cout << "CRC:" << crc << endl;
}

void PNGFile::readChunk(char (&data), const int &length) {
    int ret = fread(&data, sizeof(char), length, file);
    if (ret == 0) {
        throw std::invalid_argument("Can't read data.");
    }
}

PNGFile::PNGFile(FILE *newfile) {
    file = newfile;
    readHeader();
    uint32_t length = 0;
    readChunkHeader(length);
    parseIHDR();
    readCrc();
    readChunkHeader(length);
    char *data = new char[length]();
    cout << "LEN:" << length << endl;
    readChunk(*data, length);
    delete[] data;
}

PNGFile::~PNGFile() {
    fclose(file);
}

uint32_t PNGFile::getWidth() {
    return width;
}

uint32_t PNGFile::getHeight() {
    return height;
}
