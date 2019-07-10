#include <string.h>
#include <stdexcept>
#include <memory>
#include "image_factory.h"
#include "image_file.h"
#include "image_file_factory.h"
#include "logger.h"

ImageAllocator ImageFactory::alloc;

ImageFactory& ImageFactory::getInstance()
{
    static ImageFactory instance;
    return instance;
}

ImageSharedPtr ImageFactory::createImage(uint32_t height, uint32_t width,
                                            uint8_t frame, uint8_t component)
{
    LOG("Height:%d\n", height);
    LOG("Width:%d\n", width);
    LOG("Frame:%d\n", frame);
    LOG("Component:%d\n", component);

    return alloc.allocate(height, width, frame, component);
}

ImageSharedPtr ImageFactory::createImageFromFile(std::string fileName)
{
    ImageFileUPtr file = ImageFileUPtr{ImageFileFactory::openImageFile(fileName)};
    if (!file) {
        throw std::out_of_range("Opening file has failed");
    }
    auto frame = Configuration::getImageFrame();
    auto height = file->getHeight();
    auto width = file->getWidth();
    auto component = file->getComponentCnt();
    ImageSharedPtr img = ImageFactory::createImage(height, width, frame, component);

    auto callback = [=, &img] (uint32_t row) {
                                            return (*img)[frame + row] + frame * component;
                                            };
    file->loadImage(callback);
    img->fillFrames();

    return img;
}

ImageSharedPtr ImageFactory::createImageFromImage(ImageSharedPtr const img, ColorSpace color)
{
    switch (color) {
        case ColorSpace::Grayscale:
            return createImage(img->getImageHeight(), img->getImageWidth(),
                                img->getFrame(), 1);
        case ColorSpace::GrayscaleAlpha:
            return createImage(img->getImageHeight(), img->getImageWidth(),
                                img->getFrame(), 2);
        case ColorSpace::TrueColor:
            return createImage(img->getImageHeight(), img->getImageWidth(),
                                img->getFrame(), 3);
        case ColorSpace::TrueColorAlpha:
            return createImage(img->getImageHeight(), img->getImageWidth(),
                                img->getFrame(), 4);
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

ImageSharedPtr ImageFactory::createImageFromImage(ImageSharedPtr const img)
{
    return createImage(img->getImageHeight(), img->getImageWidth(),
                        img->getFrame(), img->getComponent());
}

bool ImageFactory::createFileFromImage(std::string name, ImageSharedPtr const img)
{
    ColorSpace color = getColorSpaceFromComponent(img->getComponent());
    ImageFileUPtr file = ImageFileUPtr{
                            ImageFileFactory::createImageFile(name,
                                                                img->getImageWidth(),
                                                                img->getImageHeight(),
                                                                8, color)};
    auto component = img->getComponent();
    auto frame = img->getFrame();
    auto callback = [=, &img] (uint32_t row) {
                                            return (*img)[frame + row] + frame * component;
                                            };
    file->saveImage(callback);
    return true;
}
