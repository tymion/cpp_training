#include <sys/stat.h>
#include "png.hpp"
#include <stdexcept>
#include <cstring>
#include <iostream>

#define PNG_HEADER_SIZE 8

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

static uint32_t getIntFromChar(uint8_t *data) {
    cout << " : " << (uint32_t)data[0] << " : " << (uint32_t)data[1] << " : " << (uint32_t)data[2] << " : " << (uint32_t)data[3] << endl;
    return (data[0] << 24) | (data[1] << 16) | (data[2] << 8) | data[3];
}

PNGChunkType PNGFile::parseData(uint32_t dataType, uint8_t *data) {
    switch (dataType) {
        case 0x49484452:
            width = getIntFromChar(data);
            height = getIntFromChar(&data[4]);
            return PNGChunkType::IHDR;
        case 0x49444154:
            return PNGChunkType::IDAT;
        default:
            return PNGChunkType::Custom;
    }
    return PNGChunkType::Custom;
}

void PNGFile::readChunkHeader(struct PNGChunk_ *chunk) {
    size_t ret = fread(chunk, sizeof(uint32_t), 2, file);
    if (ret == 0) {
        throw std::invalid_argument("Can't read file chunk header.");
    }
    if (littleEndian) {
        chunk->length = changeEndianness(chunk->length);
        chunk->typeData = changeEndianness(chunk->typeData);
    }
    cout << "Chunk data length:" << chunk->length << endl;
    cout << "Chunk Type:" << chunk->typeData << endl;
    chunk->attr = PNGChunkAttr::None;
    if (chunk->typeData & (0x1 << 5)) {
        chunk->attr |= PNGChunkAttr::Ancillary;
        cout << "Ancillary:" << 1 << endl;
    } else {
        cout << "Ancillary:" << 0 << endl;
    }
    if (chunk->typeData & (0x1 << 13)) {
        chunk->attr |= PNGChunkAttr::Private;
        cout << "Private:" << 1 << endl;
    } else {
        cout << "Private:" << 0 << endl;
    }
    if (chunk->typeData & (0x1 << 21)) {
        chunk->attr |= PNGChunkAttr::Reserved;
        cout << "Reserved:" << 1 << endl;
    } else {
        cout << "Reserved:" << 0 << endl;
    }
    if (chunk->typeData & (0x1 << 29)) {
        chunk->attr |= PNGChunkAttr::SafeToCopy;
        cout << "Safe-to-copy:" << 1 << endl;
    } else {
        cout << "Safe-to-copy:" << 0 << endl;
    }
    uint8_t *data = new uint8_t[chunk->length];
    ret = fread(data, sizeof(uint8_t), chunk->length, file);
    if (ret == 0) {
        throw std::invalid_argument("Can't read file chunk data.");
    }
    chunk->type = parseData(chunk->typeData, data);
    delete[] data;
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
    struct PNGChunk_ ihdrChunk;
    readChunkHeader(&ihdrChunk);
    readCrc();
    struct PNGChunk_ chunk;
    readChunkHeader(&chunk);
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
