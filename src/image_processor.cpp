#include <cstring>
#include <cmath>
#include "image_processor_factory.h"

ImageProcessor::ImageProcessor(uint32_t height)
{
    _data = (uint32_t**) malloc(height * sizeof(*_data));
}

ImageProcessor::~ImageProcessor()
{
    free(_data);
}

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
/*
lowPassFiter for different component images
Image& ImageProcessor::lowPassFilter(Image const& img, uint8_t kernel_size)
{
    Image& outImg = ImageFactory::createImageFromImage(img);
    auto max_width = (img.getWidth() + img.getFrame() * 2) * img.getComponent();
    auto width = img.getWidth() + img.getFrame() * 2 - kernel_size;
    auto height = img.getHeight() + img.getFrame() * 2;
    // sum up values in a row to tmp tab
    printf("=======%d===%d===\n", max_width, width *img.getComponent() + img.getComponent());
    for (auto i = 0; i < height; i++) {
        memset(_data[i], 0, max_width * sizeof(uint32_t));
        for (auto j = 0; j < width; j++) {
            for (auto n = 0; n < kernel_size; n++) {
                for (auto c = 0; c < img.getComponent(); c++) {
                    _data[i][j * img.getComponent() + c] += img[i][(j + n) * img.getComponent() + c];
                }
            }
        }
    }
    // sum up values in col from tmp tab
    auto kernel = kernel_size / 2;
    uint32_t tmp = 0;
    for (auto i = kernel; i < height - kernel; i++) {
        for (auto j = kernel; j < width + kernel; j++) {
            for (auto c = 0; c < img.getComponent(); c++) {
                for (auto n = -kernel; n <= kernel; n++) {
                    tmp += _data[i + n][(j - kernel) * img.getComponent() + c];
                }
                outImg[i][j * img.getComponent() + c] = (uint8_t) (tmp / (kernel_size * kernel_size));
                tmp = 0;
            }
        }
    }
    return outImg;
}
*/
Image& ImageProcessor::lowPassFilter(Image const& img, uint8_t kernel_size)
{
    Image& outImg = ImageFactory::createImageFromImage(img);
    auto max_width = img.getWidth() + img.getFrame() * 2;
    auto width = img.getWidth() + img.getFrame() * 2 - kernel_size;
    auto height = img.getHeight() + img.getFrame() * 2;
    auto kernel = kernel_size / 2;
    uint32_t tmp = 0;
    // sum up values in a row to tmp tab
    for (uint32_t i = kernel; i < height - kernel; i++) {
        _data[i][kernel] = img[i][0] * (kernel + 1);
        for (auto j = kernel + 1; j < kernel_size; j++) {
            _data[i][kernel] += img[i][j];
        }
        for (uint32_t j = kernel + 1; j < width - kernel; j++) {
            _data[i][j] = _data[i][j - 1] - img[i][j - (kernel + 1)] + img[i][j + kernel];
        }
    }
    for (auto i = 0; i < kernel; i++) {
        memcpy(_data[i], _data[kernel], width * sizeof(*_data[0]));
        memcpy(_data[height - 1 - i], _data[height - 1 - kernel], width * sizeof(*_data[0]));
    }
    // sum up values in col from tmp tab
    for (uint32_t j = kernel; j < width - kernel; j++) {
        tmp = _data[kernel][j] * (kernel + 1);
        for (auto i = kernel + 1; i < kernel_size; i++) {
            tmp += _data[i][j];
        }
        outImg[kernel][j] = (uint8_t) (tmp / (kernel_size * kernel_size));
        for (uint32_t i = kernel + 1; i < height - kernel; i++) {
            tmp = tmp - _data[i - (kernel + 1)][j] + _data[i + kernel][j];
            outImg[i][j] = (uint8_t) (tmp / (kernel_size * kernel_size));
        }
    }
    return outImg;
}

Image& ImageProcessor::standardDeviation(Image const& first, Image const& second, uint8_t kernel_size)
{
    Image& outImg = ImageFactory::createImageFromImage(first);
    auto width = outImg.getWidth() + outImg.getFrame() * 2;
    auto height = outImg.getHeight() + outImg.getFrame() * 2;
    int32_t tmp = 0;
    double dtmp = 0.0;
    uint8_t kernel = kernel_size / 2;
    // sum up power of subtraction values in a row to tmp tab

    for (uint32_t i = kernel; i < height - kernel; i++) {
        for (uint32_t j = kernel; j < width - kernel; j++) {
            dtmp = first[i][j] - second[i][j];
            outImg[i][j] = dtmp * dtmp;
        }
        for (uint8_t j = 0; j < kernel; j++) {
            outImg[i][j] = outImg[i][kernel];
            outImg[i][width - 1 - j] = outImg[i][width - kernel - 1];
        }
    }
    for (uint32_t i = kernel; i < height - kernel; i++) {
        _data[i][kernel] = outImg[i][0] * (kernel + 1);
        for (auto j = kernel + 1; j < kernel_size; j++) {
            _data[i][kernel] += outImg[i][j];
        }
        for (uint32_t j = kernel + 1; j < width - kernel; j++) {
            _data[i][j] = _data[i][j - 1] - outImg[i][j - (kernel + 1)] + outImg[i][j + kernel];
        }
    }
    for (auto i = 0; i < kernel; i++) {
        memcpy(_data[i], _data[kernel], width * sizeof(*_data[0]));
        memcpy(_data[height - 1 - i], _data[height - 1 - kernel], width * sizeof(*_data[0]));
    }
    for (uint32_t j = kernel; j < width - kernel; j++) {
        tmp = _data[kernel][j] * (kernel + 1);
        for (auto i = kernel + 1; i < kernel_size; i++) {
            tmp += _data[i][j];
        }
        outImg[kernel][j] = tmp;
        for (uint32_t i = kernel + 1; i < height - kernel; i++) {
            tmp = tmp - _data[i - (kernel + 1)][j] + _data[i + kernel][j];
//            outImg[i][j] = second[i][j] / sqrt(tmp / (kernel_size * kernel_size));
            outImg[i][j] = second[i][j] / sqrt(tmp);
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
