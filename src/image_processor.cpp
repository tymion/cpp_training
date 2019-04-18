#include <cstring>
#include "image_processor_factory.h"

Image& ImageProcessor::changeColorSpace(Image const& img, ColorSpace color)
{
    Image& gray_img = ImageFactory::createImageFromImage(img, color);
    uint8_t comp = img.getComponent();
    for (auto i = 0; i < img.getHeight() + img.getFrame() * 2; i++) {
        for (auto j = 0; j < img.getWidth() + img.getFrame() * 2; j++) {
            gray_img[i][j] =
                (uint8_t) ((float) img[i][j * comp] * 0.3 +
                (float) img[i][j * comp + 1] * 0.59 +
                (float) img[i][j * comp + 2] * 0.11);
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
        memset(_data[i], 0, img.getWidth() + img.getFrame() * 2);
        for (auto j = 0; j < width; j++) {
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

Image& ImageProcessor::standardDeviation(Image const& first, Image const& second, uint8_t kernel_size)
{
    Image& outImg = ImageFactory::createImageFromImage(first);
    auto width = outImg.getWidth() + outImg.getFrame() * 2 - kernel_size;
    auto height = outImg.getHeight() + outImg.getFrame() * 2;
    int32_t tmp = 0;
    // sum up power of subtraction values in a row to tmp tab
    for (auto i = 0; i < height; i++) {
        memset(_data[i], 0, first.getWidth() + first.getFrame() * 2);
        for (auto j = 0; j < width; j++) {
            for (auto n = 0; n < kernel_size; n++) {
                _data[i][j] += first[i][j + n];
            }
        }
    }
    for (auto i = 0; i < height; i++) {
        for (auto j = 0; j < width; j++) {
            tmp = first[i][j] - second[i][j];
            outImg[i][j] = tmp * tmp;
            if (outImg[i][j] < 0) {
                outImg[i][j] = 0;
            }
        }
    }
    return outImg;
}

Image& ImageProcessor::subtraction(Image const& first, Image const& second)
{
    Image& outImg = ImageFactory::createImageFromImage(first);
    for (auto i = 0; i < first.getHeight() + first.getFrame() * 2; i++) {
        for (auto j = 0; j < first.getWidth() + first.getFrame() * 2; j++) {
            outImg[i][j] = first[i][j] - second[i][j];
            if (outImg[i][j] < 0) {
                outImg[i][j] = 0;
            }
        }
    }
    return outImg;
}
