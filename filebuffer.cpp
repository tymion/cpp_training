#include "filebuffer.hpp"

FileBuffer::FileBuffer(IImage *image)
{
    _image = image;
}

FileBuffer::~FileBuffer()
{
}

bool FileBuffer::getData(Region region)
{
    return false;
}
