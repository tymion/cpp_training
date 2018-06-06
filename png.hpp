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
    Greyscale = 0x0,
    Greyscale_1 = 0x1,
    Greyscale_2 = 0x2,
    Greyscale_4 = 0x4,
    Greyscale_8 = 0x8,
    Greyscale_16 = 0x10,
    TrueColor = 0x200,
    TrueColor_8 = 0x208,
    TrueColor_16 = 0x210,
    IndexedColor = 0x300,
    IndexedColor_1 = 0x301,
    IndexedColor_2 = 0x302,
    IndexedColor_4 = 0x304,
    IndexedColor_8 = 0x308,
    GreyscaleAlpha = 0x400,
    GreyscaleAlpha_8 = 0x408,
    GreyscaleAlpha_16 = 0x410,
    TrueColorAlpha = 0x600,
    TrueColorAlpha_8 = 0x608,
    TrueColorAlpha_16 = 0x610
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
};

#endif /* _PNG_HPP_ */
