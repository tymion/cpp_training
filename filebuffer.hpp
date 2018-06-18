#ifndef _FILE_BUFFER_HPP_
#define _FILE_BUFFER_HPP_
#include <cstdbool>
#include "IImage.hpp"
#include "Region.hpp"

class FileBuffer {
    private:
        IImage *_image;
        uint8_t *_data;
        uint32_t _dataLen;

    public:
        FileBuffer(IImage *image);
        ~FileBuffer();
        bool getData(uint32_t row, uint32_t column, Region *region);
};

#endif /* _FILE_BUFFER_HPP_ */
