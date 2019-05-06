#include <string.h>
#include <stdexcept>
#include <memory>
#include "image_factory.h"
#include "image_file.h"
#include "image_file_factory.h"
#include "logger.h"

ImageAllocator ImageFactory::_allocator;
uint32_t ImageFactory::_used;
uint8_t ImageFactory::_pixel[STORAGE_SIZE];

void ImageDeleter(Image* img)
{
    ImageFactory::deleteImage(img);
}

ImageFactory& ImageFactory::getInstance()
{
    static ImageFactory instance;
    return instance;
}

void ImageFactory::assignStorage(Image& img, auto height, auto width)
{
    for (auto i = 0; i < height; i++) {
        img._data[i] = &ImageFactory::_pixel[ImageFactory::_used];
        ImageFactory::_used += width;
    }
}

void ImageFactory::deleteImage(Image *img)
{
    ImageFactory::_allocator.deallocate(img);
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
    Image& img = *ImageFactory::_allocator.allocate(image_height);
    img._height = height;
    img._width = width;
    img._frame = frame;
    img._component = component;

    LOG("Height:%d\n", height);
    LOG("Width:%d\n", width);
    LOG("Frame:%d\n", frame);
    LOG("Component:%d\n", component);

    ImageFactory::assignStorage(img, image_height, image_width);

    return img;
}

Image& ImageFactory::createImageFromFile(std::string fileName)
{
    ImageFileUPtr file = ImageFileUPtr{ImageFileFactory::openImageFile(fileName)};
    if (!file) {
        throw std::out_of_range("Opening file has failed");
    }
    auto frame = Configuration::getImageFrame();
    auto height = file->getHeight();
    auto width = file->getWidth();
    auto component = file->getComponentCnt();
    Image& img = ImageFactory::createImage(height, width, frame, component);

    auto callback = [=, &img] (uint32_t row) {
                                            return img[frame + row] + frame * component;
                                            };
    file->loadImage(callback);
    img.fillFrames();

    return img;
}

Image& ImageFactory::createImageFromImage(Image const& img, ColorSpace color)
{
    switch (color) {
        case ColorSpace::Grayscale:
            return createImage(img.getHeight(), img.getWidth(), img.getFrame(), 1);
        case ColorSpace::GrayscaleAlpha:
            return createImage(img.getHeight(), img.getWidth(), img.getFrame(), 2);
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
    auto component = img.getComponent();
    auto frame = img.getFrame();
    auto callback = [=, &img] (uint32_t row) {
                                            return img[frame + row] + frame * component;
                                            };
    file->saveImage(callback);
    return true;
}
