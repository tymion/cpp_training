#ifndef _FILE_BUFFER_H_
#define _FILE_BUFFER_H_
#include <cstdbool>
#include "iimage.h"
#include "region.h"

class FileBuffer {
    private:
        IImage *_image;
        uint8_t _component;
        uint8_t *_data;
        uint32_t _dataLen;

    public:
        FileBuffer(IImage *image);
        ~FileBuffer();
        RegionBase* createRegion(uint32_t height, uint32_t width);
        bool updateRegion(uint32_t row, uint32_t column, RegionBase *region);
};

#endif /* _FILE_BUFFER_H_ */
