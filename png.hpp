#ifndef _PNG_HPP_
#define _PNG_HPP_
#include "IImage.hpp"
#include <cstdio>
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
    Custom
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
    FILE *file;
    uint32_t height;
    uint32_t width;
    bool littleEndian;

    bool readHeader();
    void readChunkHeader(struct PNGChunk_ *chunk);
    void readChunk(char &data, const int &length);
    void readCrc();
    PNGChunkType parseData(uint32_t dataType, uint8_t *data);

public:
    PNGFile(FILE *newfile);
    ~PNGFile();
    uint32_t getHeight();
    uint32_t getWidth();
};

#endif /* _PNG_HPP_ */
