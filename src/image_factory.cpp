#include "image_factory.h"
#include <stdexcept>

ImageFactory& ImageFactory::getInstance()
{
    static ImageFactory instance;
    return instance;
}

Image& ImageFactory::createImage(uint32_t height, uint32_t width)
{
    uint8_t frame = 3;
    uint32_t image_height = 0;
    uint32_t image_width = 0;
    if (height + 2 * frame < height || width + 2 * frame < width) {
        frame = 0;
        image_height = height;
        image_width = width;
    } else {
        image_height = height + 2 * frame;
        image_width = width + 2 * frame;
    }
    if (image_width * image_height > STORAGE_SIZE - _used) {
        throw std::out_of_range("Image side is out of factory range.");
    }
    Image& img = getInstance()._warehouse.emplace_back(image_height);
    img._height = height;
    img._width = width;
    img._frame = frame;
    for (uint32_t i = 0; i < image_height; i++) {
        img._data[i] = _pixel[_used + i * image_width];
    }
    _used += image_height * image_width;
    return img;
}
