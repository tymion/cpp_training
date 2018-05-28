#ifndef _PNG_HPP_
#define _PNG_HPP_
#include "IImage.hpp"
#include <cstdio>
#include <cstdint>

using namespace std;

enum PNGChunkType {
    Invalid = -1,
    IHDR,
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
    Ancillary = 1,
    Private = 2,
    Reserved = 4,
    SafeToCopy = 8
};

struct PNGChunk_ {
    enum PNGChunkType type;
    enum PNGChunkAttr attr;
    uint32_t length;
};

class PNGFile: public IImage {
private:
    FILE *file;
    uint32_t height;
    uint32_t width;
    bool littleEndian;

    bool readHeader();
    PNGChunkAttr readChunkHeader(uint32_t &length);
    void readChunk(char &data, const int &length);
    void readCrc();
    void parseIHDR();

public:
    PNGFile(FILE *newfile);
    ~PNGFile();
    uint32_t getHeight();
    uint32_t getWidth();
};

#endif /* _PNG_HPP_ */
