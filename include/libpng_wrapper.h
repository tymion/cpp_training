#ifndef _PNG_H_
#define _PNG_H_
#include "iimage.h"
#include <cstdio>
#include <cstdbool>
#include <cstdint>

using namespace std;

class PNGFile: public IImage {
    private:
        FILE *_file;
        png_structp _png;
        png_infop _info;
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

#endif /* _PNG_H_ */
