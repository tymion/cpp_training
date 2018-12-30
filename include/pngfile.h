#pragma once
#include "iimage.h"
#include <cstdio>
#include <cstdbool>
#include <cstdint>

enum PNGChunkType {
    IHDR = 0,
    IDAT,
    PLTE,
    tRNS,
    cHRM,
    gAMA,
    iCCP,
    sBIT,
    sRGB,
    tEXt,
    iTXt,
    zTXt,
    bKGD,
    hIST,
    sPLT,
    tIME,
    IEND,
    Custom
};

enum PNGImageType {
    Invalid             = -1,
    Greyscale           = 0x0000,
    Greyscale_1         = 0x0001,
    Greyscale_2         = 0x0002,
    Greyscale_4         = 0x0004,
    Greyscale_8         = 0x0008,
    Greyscale_16        = 0x0010,
    IndexedColor        = 0x0300,
    IndexedColor_1      = 0x0301,
    IndexedColor_2      = 0x0302,
    IndexedColor_4      = 0x0304,
    IndexedColor_8      = 0x0308,
    GreyscaleAlpha      = 0x0400,
    GreyscaleAlpha_8    = 0x0408,
    GreyscaleAlpha_16   = 0x0410,
    TrueColor           = 0x0200,
    TrueColor_8         = 0x0208,
    TrueColor_16        = 0x0210,
    TrueColorAlpha      = 0x0600,
    TrueColorAlpha_8    = 0x0608,
    TrueColorAlpha_16   = 0x0610
};

enum PNGFileState {
    Open,
    Data,
    Closed,
};

enum PNGChunkAttr {
    None = 0,
    Ancillary = 1,
    Private = 2,
    Reserved = 4,
    SafeToCopy = 8
};

struct PNGChunk_ {
    uint32_t length;
    uint32_t typeData;
    enum PNGChunkType type;
    uint8_t attr;
};

class PNGFile: public IImage {
    private:
        FILE *_file;
        uint32_t _height;
        uint32_t _width;
        enum PNGImageType _type;
        enum PNGFileState _state;
        struct PNGChunk_ _ihdr;
        uint32_t _dataLeft;
        bool _littleEndian;

        bool readHeader();
        PNGChunkType readChunkHeader(struct PNGChunk_ *chunk);
        void readCrc();
        PNGChunkType parseData(uint32_t dataType, uint8_t *data);
        PNGImageType parseColor(uint8_t colorType, uint8_t depth);
        template <class T>
            size_t readData(T *data, size_t len) {
                return fread(data, sizeof(T), len, _file);
            }

    public:
        PNGFile(FILE *newfile);
        ~PNGFile();
        uint32_t getHeight();
        uint32_t getWidth();
        bool getData(uint32_t row, uint8_t **data);
        uint8_t getComponentSize();
        uint8_t getComponentCnt();
        void setDataProvider(std::function<uint8_t(uint32_t)> func);
};
