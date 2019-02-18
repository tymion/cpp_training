#include <cstdlib>
#include "image_factory.h"

Image::Image(uint32_t height)
{
    _data = (uint8_t**) malloc(height * sizeof(_data));
}

Image::~Image()
{
    free(_data);
}

uint32_t Image::getWidth() const
{
    return _width;
}

uint32_t Image::getHeight() const
{
    return _height;
}

uint8_t Image::getFrame() const
{
    return _frame;
}

uint8_t Image::getComponent() const
{
    return _component;
}

uint8_t* Image::operator[](uint32_t index) const
{
     return _data[index];
}
