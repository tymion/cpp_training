#ifndef _PNG_HPP_
#define _PNG_HPP_
#include "IImage.hpp"
#include <cstdio>
#include <cstdbool>
#include <cstdint>

using namespace std;

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
    Invalid = -1,
    Greyscale = 0x1100,
    Greyscale_1 = 0x1101,
    Greyscale_2 = 0x1102,
    Greyscale_4 = 0x1104,
    Greyscale_8 = 0x1108,
    Greyscale_16 = 0x1110,
    IndexedColor = 0x2100,
    IndexedColor_1 = 0x2101,
    IndexedColor_2 = 0x2102,
    IndexedColor_4 = 0x2104,
    IndexedColor_8 = 0x2108,
    GreyscaleAlpha = 0x3200,
    GreyscaleAlpha_8 = 0x3208,
    GreyscaleAlpha_16 = 0x3210,
    TrueColor = 0x4300,
    TrueColor_8 = 0x4308,
    TrueColor_16 = 0x4310,
    TrueColorAlpha = 0x5400,
    TrueColorAlpha_8 = 0x5408,
    TrueColorAlpha_16 = 0x5410
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
        uint32_t getData(uint8_t *data, uint32_t length);
        uint8_t getComponentSize();
        uint8_t getComponentCnt();
};

#endif /* _PNG_HPP_ */
