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

void ImageFactory::assignStorage(Image& img, auto height, auto width)
{
    for (auto i = 0; i < height; i++) {
        img._data[i] = &ImageFactory::_pixel[_used + i * width];
    }
    ImageFactory::_used += height * width;
}

Image& ImageFactory::createImage(auto height, auto width, auto frame, auto component)
{
    auto image_height = height + 2 * frame;
    auto image_width = (width + 2 * frame) * component;
    if (image_height < height || image_width < width) {
        throw std::out_of_range("After adding frame integer overflow");
    }
    if (image_width * image_height > STORAGE_SIZE - _used) {
        throw std::out_of_range("Image side is out of factory range.");
    }
    Image& img = getInstance()._warehouse.emplace_back(image_height);
    img._height = height;
    img._width = width;
    img._frame = frame;
    img._component = component;

    std::cout << "Height:" << height << "\n";
    std::cout << "Width:" << width << "\n";
    std::cout << "Frame:" << (uint32_t) frame << "\n";
    std::cout << "Component:" << (uint32_t) component << "\n";

    ImageFactory::assignStorage(img, image_height, image_width);

    return img;
}

Image& ImageFactory::createImageFromFile(std::string fileName)
{
    uint8_t frame = Configuration::getImageFrame();
    ImageFileUPtr file = ImageFileUPtr{ImageFileFactory::openImageFile(fileName)};
    auto height = file->getHeight();
    auto width = file->getWidth();
    auto component = file->getComponentCnt();
    Image& img = ImageFactory::createImage(height, width, frame, component);

    auto callback = [=, &img] (uint32_t row) { return img[frame + row] + frame; };
    file->loadImage(callback);

//    img.fillFrames();

    return img;
}

Image& ImageFactory::createImageFromImage(Image const& img, ColorSpace color)
{
    switch (color) {
        case ColorSpace::Grayscale:
            return createImage(img.getHeight(), img.getWidth(), img.getFrame(), 3);
        case ColorSpace::GrayscaleAlpha:
            return createImage(img.getHeight(), img.getWidth(), img.getFrame(), 4);
        case ColorSpace::TrueColor:
            return createImage(img.getHeight(), img.getWidth(), img.getFrame(), 3);
        case ColorSpace::TrueColorAlpha:
            return createImage(img.getHeight(), img.getWidth(), img.getFrame(), 4);
        default:
            throw std::invalid_argument("Unknown color space.");
    }
}

ColorSpace ImageFactory::getColorSpaceFromComponent(size_t component)
{
    switch (component) {
        case 1:
            return ColorSpace::Grayscale;
        case 2:
            return ColorSpace::GrayscaleAlpha;
        case 3:
            return ColorSpace::TrueColor;
        case 4:
            return ColorSpace::TrueColorAlpha;
        default:
            throw std::invalid_argument("Invalid component value");
    }
}

Image& ImageFactory::createImageFromImage(Image const& img)
{
    return createImage(img.getHeight(), img.getWidth(), img.getFrame(), img.getComponent());
}

bool ImageFactory::createFileFromImage(std::string name, Image const& img)
{
    ColorSpace color = getColorSpaceFromComponent(img.getComponent());
    ImageFileUPtr file = ImageFileUPtr{ImageFileFactory::createImageFile(name, img.getWidth(),
            img.getHeight(), 8, color)};
    auto callback = [&img](uint32_t row) {
                                            uint8_t frame = img.getFrame();
                                            return img[frame + row] + frame;
                                        };
    file->saveImage(callback);
    return true;
}
