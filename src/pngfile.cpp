#include <sys/stat.h>
#include "pngfile.h"
#include <stdexcept>
#include <cstring>
#include <iostream>

#define PNG_HEADER_SIZE 8

static uint32_t
changeEndianness(uint32_t value)
{
    uint32_t result = 0;
    result |= (value & 0x000000FF) << 24;
    result |= (value & 0x0000FF00) << 8;
    result |= (value & 0x00FF0000) >> 8;
    result |= (value & 0xFF000000) >> 24;
    return result;
}

bool PNGFile::readHeader() {
    uint32_t header[PNG_HEADER_SIZE/sizeof(uint32_t)];
    int ret = 0;
    ret = fread(header, sizeof(uint32_t), PNG_HEADER_SIZE/sizeof(uint32_t), _file);
    if (ret == 0) {
        throw std::invalid_argument("Can't read file header for endianness check.");
    }
    if (header[0] == 1196314761 && header[1] == 169478669) {
        // little endian
        _littleEndian = true;
    }
    return true;
}

static uint32_t
getIntFromChar(uint8_t *data) {
    return (data[0] << 24) | (data[1] << 16) | (data[2] << 8) | data[3];
}

PNGImageType PNGFile::parseColor(uint8_t colorType, uint8_t depth) {
    switch (colorType << 8 | depth) {
        case Greyscale:
        case Greyscale_1:
        case Greyscale_2:
        case Greyscale_4:
        case Greyscale_8:
        case Greyscale_16:
        case TrueColor:
        case TrueColor_8:
        case TrueColor_16:
        case IndexedColor:
        case IndexedColor_1:
        case IndexedColor_2:
        case IndexedColor_4:
        case IndexedColor_8:
        case GreyscaleAlpha:
        case GreyscaleAlpha_8:
        case GreyscaleAlpha_16:
        case TrueColorAlpha:
        case TrueColorAlpha_8:
        case TrueColorAlpha_16:
            std::cout << "Image Type:" << std::hex << (colorType << 8 | depth) << std::dec << std::endl;
            return (PNGImageType) (colorType << 8 | depth);
        default:
            std::cout << "std::invalid Image Type! (" << (colorType << 8 | depth) << ")" << std::endl;
            return Invalid;
    }
}

PNGChunkType PNGFile::parseData(uint32_t dataType, uint8_t *data) {
    switch (dataType) {
        case 0x49484452:
            _width = getIntFromChar(data);
            _height = getIntFromChar(&data[4]);
            _type = parseColor(data[9], data[8]);
            return PNGChunkType::IHDR;
        case 0x49444154:
            return PNGChunkType::IDAT;
        default:
            std::cout << "Unknown chunk type:" << (0xff & dataType) << std::endl;
            return PNGChunkType::Custom;
    }
    return PNGChunkType::Custom;
}

PNGChunkType PNGFile::readChunkHeader(struct PNGChunk_ *chunk) {
    size_t ret = readData((uint32_t *) chunk, (size_t) 2);
    if (ret == 0) {
        throw std::invalid_argument("Can't read file chunk header.");
    }
    if (_littleEndian) {
        chunk->length = changeEndianness(chunk->length);
        chunk->typeData = changeEndianness(chunk->typeData);
    }
    std::cout << "===Reading new chunk===" << std::endl;
    std::cout << "Chunk data length:" << chunk->length << std::endl;
    std::cout << "Chunk Type:" << std::hex << chunk->typeData << std::dec << std::endl;
    chunk->attr = PNGChunkAttr::None;
    if (chunk->typeData & (0x1 << 5)) {
        chunk->attr |= PNGChunkAttr::Ancillary;
        std::cout << "Ancillary:" << 1 << std::endl;
    } else {
        std::cout << "Ancillary:" << 0 << std::endl;
    }
    if (chunk->typeData & (0x1 << 13)) {
        chunk->attr |= PNGChunkAttr::Private;
        std::cout << "Private:" << 1 << std::endl;
    } else {
        std::cout << "Private:" << 0 << std::endl;
    }
    if (chunk->typeData & (0x1 << 21)) {
        chunk->attr |= PNGChunkAttr::Reserved;
        std::cout << "Reserved:" << 1 << std::endl;
    } else {
        std::cout << "Reserved:" << 0 << std::endl;
    }
    if (chunk->typeData & (0x1 << 29)) {
        chunk->attr |= PNGChunkAttr::SafeToCopy;
        std::cout << "Safe-to-copy:" << 1 << std::endl;
    } else {
        std::cout << "Safe-to-copy:" << 0 << std::endl;
    }
    uint8_t *data = new uint8_t[chunk->length];
    ret = readData(data, chunk->length);
    if (ret == 0) {
        throw std::invalid_argument("Can't read file chunk data.");
    }
    chunk->type = parseData(chunk->typeData, data);
    if (PNGChunkType::IDAT == chunk->type) {
        _state = PNGFileState::Data;
        _dataLeft = chunk->length;
    } else if (PNGChunkType::IEND == chunk->type) {
        _state = PNGFileState::Closed;
    }
    delete[] data;
    return chunk->type;
}

void PNGFile::readCrc() {
    uint32_t crc;
    size_t ret = readData(&crc, 1);
    if (ret == 0) {
        throw std::invalid_argument("Can't read crc.");
    }

    std::cout << "CRC:" << crc << std::endl;
}

PNGFile::PNGFile(FILE *file) {
    if (file == NULL) {
        throw std::invalid_argument("std::invalid file descriptor.");
    }
    _file = file;
    readHeader();
    readChunkHeader(&_ihdr);
    readCrc();
    _state = PNGFileState::Open;
    struct PNGChunk_ chunk;
    while (_state == PNGFileState::Open) {
        readChunkHeader(&chunk);
    }
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

bool PNGFile::getData(uint32_t row, uint8_t **data) {
    // This function need fixing
    if (_state == PNGFileState::Closed) {
        return 0;
    }
    /*
    size_t ret = 0;
    size_t tmp = 0;
    uint32_t toRead = length;
    std::cout << "getData|toRead:" << toRead << std::std::endl;
    while (_state == PNGFileState::Data && ret != length) {
        std::cout << "getData" << std::std::endl;
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
*/
    return true;
}

void PNGFile::setDataProvider(std::function<uint8_t(uint32_t)> func) {
}
