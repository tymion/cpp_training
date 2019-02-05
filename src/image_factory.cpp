#include <string.h>
#include <stdexcept>
#include <memory>
#include "image_factory.h"
#include "image_file.h"
#include "image_file_factory.h"

uint32_t ImageFactory::_used;
uint8_t ImageFactory::_pixel[STORAGE_SIZE];

ImageFactory& ImageFactory::getInstance()
{
    static ImageFactory instance;
    instance._warehouse.reserve(4);
    return instance;
}

Image* ImageFactory::createImage(uint32_t height, uint32_t width)
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
//    Image& img = getInstance()._warehouse.emplace_back(image_height);
    Image *img = new Image(image_height);
    img->_height = height;
    img->_width = width;
    img->_frame = frame;
    for (uint32_t i = 0; i < image_height; i++) {
        img->_data[i] = &ImageFactory::_pixel[_used + i * image_width];
    }
    ImageFactory::_used += image_height * image_width;
    return img;
}

Image& ImageFactory::createImageFromFile(std::string fileName)
{
    uint8_t frame = 3;
    uint32_t image_height = 0;
    uint32_t image_width = 0;
    std::unique_ptr<ImageFile> file = std::unique_ptr<ImageFile>{ImageFileFactory::createImageFile(fileName)};
    uint32_t height = file->getHeight();
    uint32_t width = file->getWidth();
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
        img._data[i] = &ImageFactory::_pixel[_used + i * image_width];
    }
    ImageFactory::_used += image_height * image_width;
    auto callback = [=, &img] (uint32_t row) { return img[frame + row] + frame; };
    file->loadImage(callback);
    for (auto i = 0; i < frame; i++) {
        memcpy(img[i], img[frame], width);
        memcpy(img[frame + height + i], img[frame + height - 1], width);
    }
    for (auto j = 0; j < frame; j++) {
        for (auto i = 0; i < image_height; i++) {
            img[i][j] = img[i][frame];
            img[i][frame + width + j] = img[i][frame + height];
        }
    }
    return img;
}
