#include <cstdlib>
#include <string.h>
#include <stdexcept>
#include "image.h"

Image::Image(uint32_t height, uint32_t width, uint8_t frame, uint8_t component,
                uint8_t **data) :
                                Matrix<uint8_t>(height + 2 * frame,
                                                (width + 2 * frame) * component, data),
                                _height(height), _width(width), _frame(frame), _component(component)
{
}

Image::~Image()
{
}

uint32_t Image::getImageHeight() const
{
    return _height;
}

uint32_t Image::getImageWidth() const
{
    return _width;
}

uint8_t Image::getFrame() const
{
    return _frame;
}

uint8_t Image::getComponent() const
{
    return _component;
}

void Image::fillFrames()
{
    for (auto i = 0; i < _frame; i++) {
        memcpy(&_data[i][_frame * _component], &_data[_frame][_frame * _component], _width * _component);
        memcpy(&_data[_frame + _height + i][_frame * _component], &_data[_frame + _height - 1][_frame * _component], _width * _component);
    }
    for (uint32_t j = 0; j < _frame * _component; j++) {
        for (uint32_t i = 0; i < _height + 2 * _frame; i++) {
            _data[i][j] = _data[i][_frame * _component + (j % _component)];
            _data[i][(_frame + _width) * _component + j] = _data[i][(_frame + _width - 1) * _component + j % _component];
        }
    }
}
