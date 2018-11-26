#include "image_factory.h"

ImageFactory& ImageFactory::getInstance()
{
    static ImageFactory instance;
    return instance;
}

Image& ImageFactory::createImage(uint32_t height, uint32_t width)
{
    uint8_t frame = 3;
    uint32_t image_height = 0;
    if (height + 2 * frame < height) {
        frame = 0;
        image_height = height;
    } else {
        image_height = height + 2 * frame;
    }
    Image& img = getInstance()._warehouse.emplace_back(image_height);
    img._height = height;
    img._width = width;
    img._frame = frame;
    return img;
}
