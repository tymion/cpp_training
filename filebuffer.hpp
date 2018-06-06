#ifndef _FILE_BUFFER_HPP_
#define _FILE_BUFFER_HPP_
#include <cstdbool>
#include "IImage.hpp"
#include "Region.hpp"

class FileBuffer {
    private:
        IImage *_image;

    public:
        FileBuffer(IImage *image);
        ~FileBuffer();
        bool getData(Region region);
};

#endif /* _FILE_BUFFER_HPP_ */
