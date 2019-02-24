#include <cstdlib>
#include <string.h>
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

uint8_t* Image::operator[](uint32_t index)
{
     return _data[index];
}

void Image::fillFrames()
{
    for (auto i = 0; i < _frame; i++) {
        memcpy(&_data[i][_frame], &_data[_frame][_frame], _width * _component);
        memcpy(&_data[_frame + _height + i][_frame], &_data[_frame + _height - 1][_frame], _width * _component);
    }
    for (auto j = 0; j < _frame * _component; j++) {
        for (auto i = 0; i < _height + 2 * _frame; i++) {
            _data[i][j] = _data[i][_frame * _component + j % _component];
            _data[i][(_frame + _width) * _component + j] = _data[i][(_frame + _width - 1) * _component + j % _component];
        }
    }
}
