#include "image_processor_factory.h"

Image& ImageProcessor::changeColorSpace(Image const& img, ColorSpace color)
{
    Image& gray_img = ImageFactory::createImageFromImage(img, color);
    for (auto i = 0; i < img.getHeight() + img.getFrame() * 2; i++) {
        for (auto j = 0; j < img.getWidth() + img.getFrame() * 2; j++) {
            for (auto k = 0; k < img.getComponent(); k++) {
                gray_img[i][j] += img[i][j * img.getComponent() + k];
            }
        }
    }
    return gray_img;
}
