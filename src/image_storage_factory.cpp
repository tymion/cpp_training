#include <stdexcept>
#include <memory>
#include "image_storage_factory.h"
#include "iimage.h"
#include "loader.h"

uint32_t ImageStorageFactory::_used;
uint8_t ImageStorageFactory::_pixel[STORAGE_SIZE];

ImageStorageFactory& ImageStorageFactory::getInstance()
{
    static ImageStorageFactory instance;
    return instance;
}

ImageStorage& ImageStorageFactory::createImage(std::string filename)
{
    std::unique_ptr<IImage> image(Loader::loadImage(filename));
    uint8_t frame = 3;
    uint32_t image_height = 0;
    uint32_t image_width = 0;
    uint32_t height = image->getHeight();
    uint32_t width = image->getWidth();
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
    ImageStorage& img = getInstance()._warehouse.emplace_back(image_height);
    img._height = height;
    img._width = width;
    img._frame = frame;
    for (uint32_t i = 0; i < image_height; i++) {
        img._data[i] = &ImageStorageFactory::_pixel[_used + i * image_width];
    }
    ImageStorageFactory::_used += image_height * image_width;
    return img;
}