#include "image_processor_factory.h"

Image& ImageProcessor::changeColorSpace(Image const& img, ColorSpace color)
{
    Image& gray_img = ImageFactory::createImageFromImage(img, color);
    uint8_t tmp = 0;
    for (auto i = 0; i < img.getHeight() + img.getFrame() * 2; i++) {
        for (auto j = 0; j < img.getWidth() + img.getFrame() * 2; j++) {
            gray_img[i][j] =
                (uint8_t) ((float) img[i][j * img.getComponent()] * 0.3 +
                (float) img[i][j * img.getComponent() + 1] * 0.59 +
                (float) img[i][j * img.getComponent() + 2] * 0.11);
        }
    }
    return gray_img;
}

Image& ImageProcessor::lowPassFilter(Image const& img, uint8_t kernel_size)
{
    Image& outImg = ImageFactory::createImageFromImage(img);
    auto width = img.getWidth() + img.getFrame() * 2 - kernel_size;
    auto height = img.getHeight() + img.getFrame() * 2;
    // sum up values in a row to tmp tab
    for (auto i = 0; i < height; i++) {
        for (auto j = 0; j < width; j++) {
            _data[i][j] = 0;
            for (auto n = 0; n < kernel_size; n++) {
                _data[i][j] += img[i][j + n];
            }
        }
    }
    // sum up values in col from tmp tab
    auto kernel = kernel_size / 2;
    uint32_t tmp = 0;
    for (auto i = kernel; i < height - kernel; i++) {
        for (auto j = kernel; j < width + kernel; j++) {
            for (auto n = -kernel; n <= kernel; n++) {
                tmp += _data[i + n][j - kernel];
            }
            outImg[i][j] = (uint8_t) (tmp / (kernel_size * kernel_size));
            tmp = 0;
        }
    }
    return outImg;
}

Image& ImageProcessor::subtraction(Image const& first, Image const& second)
{
    Image& outImg = ImageFactory::createImageFromImage(first);
    return outImg;
}
