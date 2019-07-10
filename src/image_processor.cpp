#include <cstring>
#include <cmath>
#include "image_processor.h"
#include "image_factory.h"

ImageProcessor::ImageProcessor(uint32_t height, uint32_t width, uint32_t **data) :
                                Matrix<uint32_t>(height, width, data)
{
}

ImageProcessor::ImageProcessor(uint32_t height, uint32_t width, uint32_t **data, uint32_t **ext) :
                                Matrix<uint32_t>(height, width, data), _ext(ext)
{
}

ImageSharedPtr ImageProcessor::changeColorSpace(ImageSharedPtr const img, ColorSpace color)
{
    ImageSharedPtr gray_img = ImageFactory::createImageFromImage(img, color);
    uint8_t comp = img->getComponent();
    for (uint32_t i = 0; i < img->getImageHeight() + img->getFrame() * 2; i++) {
        for (uint32_t j = 0; j < img->getImageWidth() + img->getFrame() * 2; j++) {
            (*gray_img)[i][j] =
                (uint8_t) ((float) (*img)[i][j * comp] * 0.3 +
                (float) (*img)[i][j * comp + 1] * 0.59 +
                (float) (*img)[i][j * comp + 2] * 0.11);
        }
    }
    return gray_img;
}

/*
lowPassFiter for different component images
ImageSharedPtr ImageProcessor::lowPassFilter(ImageSharedPtr const img, uint8_t kernel_size)
{
    ImageSharedPtr outImg = ImageFactory::createImageFromImage(img);
    auto max_width = (img->getWidth() + img->getFrame() * 2) * img->getComponent();
    auto width = img->getImageWidth() + img->getFrame() * 2 - kernel_size;
    auto height = img->getImageHeight() + img->getFrame() * 2;
    // sum up values in a row to tmp tab
    printf("=======%d===%d===\n", max_width, width *img->getComponent() + img->getComponent());
    for (auto i = 0; i < height; i++) {
        memset(_data[i], 0, max_width * sizeof(uint32_t));
        for (auto j = 0; j < width; j++) {
            for (auto n = 0; n < kernel_size; n++) {
                for (auto c = 0; c < img->getComponent(); c++) {
                    _data[i][j * img->getComponent() + c] += img[i][(j + n) * img->getComponent() + c];
                }
            }
        }
    }
    // sum up values in col from tmp tab
    auto kernel = kernel_size / 2;
    uint32_t tmp = 0;
    for (auto i = kernel; i < height - kernel; i++) {
        for (auto j = kernel; j < width + kernel; j++) {
            for (auto c = 0; c < img->getComponent(); c++) {
                for (auto n = -kernel; n <= kernel; n++) {
                    tmp += _data[i + n][(j - kernel) * img->getComponent() + c];
                }
                outImg[i][j * img->getComponent() + c] = (uint8_t) (tmp / (kernel_size * kernel_size));
                tmp = 0;
            }
        }
    }
    return outImg;
}
*/
ImageSharedPtr ImageProcessor::lowPassFilter(ImageSharedPtr const img, uint8_t kernel_size)
{
    ImageSharedPtr outImg = ImageFactory::createImageFromImage(img);
    auto width = img->getImageWidth() + img->getFrame() * 2;
    auto height = img->getImageHeight() + img->getFrame() * 2;
    auto kernel = kernel_size / 2;
    uint32_t tmp = 0;
    // sum up values in a row to tmp tab
    for (uint32_t h = kernel; h < height - kernel; h++) {
        _data[h][kernel] = (*img)[h][0] * (kernel + 1);
        for (auto w = kernel + 1; w < kernel_size; w++) {
            _data[h][kernel] += (*img)[h][w];
        }
        for (uint32_t w = kernel + 1; w < width - kernel; w++) {
            _data[h][w] = _data[h][w - 1] - (*img)[h][w - (kernel + 1)] + (*img)[h][w + kernel];
        }
    }
    for (auto h = 0; h < kernel; h++) {
        memcpy(_data[h], _data[kernel], width * sizeof(*_data[0]));
        memcpy(_data[height - 1 - h], _data[height - 1 - kernel], width * sizeof(*_data[0]));
    }
    // sum up values in col from tmp tab
    for (uint32_t w = kernel; w < width - kernel; w++) {
        tmp = _data[kernel][w] * (kernel + 1);
        for (auto h = kernel + 1; h < kernel_size; h++) {
            tmp += _data[h][w];
        }
        (*outImg)[kernel][w] = (uint8_t) (tmp / (kernel_size * kernel_size));
        for (uint32_t h = kernel + 1; h < height - kernel; h++) {
            tmp = tmp - _data[h - (kernel + 1)][w] + _data[h + kernel][w];
            (*outImg)[h][w] = (uint8_t) (tmp / (kernel_size * kernel_size));
        }
    }
    return outImg;
}

void ImageProcessor::horizontalConvolution(ImageSharedPtr const in, ImageSharedPtr out,
                                            uint32_t height, uint32_t width, uint8_t kernel_size)
{
    uint8_t frame = kernel_size / 2;
    int32_t tmp = 0;
    uint32_t w = 0;
    for (uint32_t h = 0; h < height - kernel_size; h++) {
        for (w = 0; w < kernel_size; w++) {
            tmp += (*in)[h][w];
        }
        (*out)[h][frame++] = tmp / kernel_size;
        for (w = 1; w < width - kernel_size; w++, frame++) {
            tmp = tmp - (*in)[h][w - 1] + (*in)[h][w + kernel_size - 1];
            (*out)[h][frame] = tmp / kernel_size;
        }
        frame = kernel_size / 2;
    }
}

void ImageProcessor::verticalConvolution(ImageSharedPtr const in, ImageSharedPtr out,
                                            uint32_t height, uint32_t width, uint8_t kernel_size)
{
    uint8_t frame = kernel_size / 2;
    int32_t tmp = 0;
    uint32_t h = 0;
    for (uint32_t w = 0; w < width - kernel_size; w++) {
        for (h = 0; h < kernel_size; h++) {
            tmp += (*in)[h][w];
        }
        (*out)[frame][w] = tmp / kernel_size;
        for (h = 1; h < height - kernel_size; h++) {
            tmp = tmp - (*in)[h - 1][w] + (*in)[h + kernel_size - 1][w];
            (*out)[frame + h][w] = tmp / kernel_size;
        }
    }
}

void ImageProcessor::boxConvolution(ImageSharedPtr const in, ImageSharedPtr out,
                                    uint32_t height, uint32_t width, uint8_t kernel_size)
{
    ImageSharedPtr tmp = ImageFactory::createImageFromImage(in);
//    ImageProcessor::horizontalConvolution(in, tmp, height, width, kernel_size);
    ImageProcessor::horizontalConvolution(in, out, height, width, kernel_size);
//    ImageProcessor::verticalConvolution(tmp, out, height, width, kernel_size);
}

void ImageProcessor::fastGaussianConvolution(ImageSharedPtr const in, ImageSharedPtr out,
                                                uint32_t height, uint32_t width,
                                                uint8_t kernel_size)
{
    ImageSharedPtr tmp = ImageFactory::createImageFromImage(in);
    ImageProcessor::boxConvolution(in, out, height, width, kernel_size);
//    ImageProcessor::boxConvolution(out, tmp, height, width, kernel_size);
//    ImageProcessor::boxConvolution(tmp, out, height, width, kernel_size);
}

ImageSharedPtr ImageProcessor::gaussian(ImageSharedPtr const in, uint8_t kernel_size)
{
    ImageSharedPtr out = ImageFactory::createImageFromImage(in);
    ImageProcessor::fastGaussianConvolution(in, out, in->getImageHeight(),
                                            in->getImageWidth(), kernel_size);
    return out;
}

ImageSharedPtr
ImageProcessor::standardDeviation(ImageSharedPtr const first,
                                    ImageSharedPtr const second,
                                    uint8_t kernel_size)
{
    ImageSharedPtr outImg = ImageFactory::createImageFromImage(first);
    auto width = outImg->getImageWidth() + outImg->getFrame() * 2;
    auto height = outImg->getImageHeight() + outImg->getFrame() * 2;
    int32_t tmp = 0;
    double dtmp = 0.0;
    uint8_t kernel = kernel_size / 2;
    // sum up power of subtraction values in a row to tmp tab

    for (uint32_t h = kernel; h < height - kernel; h++) {
        for (uint32_t w = kernel; w < width - kernel; w++) {
            dtmp = (*first)[h][w] - (*second)[h][w];
            (*outImg)[h][w] = dtmp * dtmp;
        }
        for (uint8_t w = 0; w < kernel; w++) {
            (*outImg)[h][w] = (*outImg)[h][kernel];
            (*outImg)[h][width - 1 - w] = (*outImg)[h][width - kernel - 1];
        }
    }
    for (uint32_t h = kernel; h < height - kernel; h++) {
        _data[h][kernel] = (*outImg)[h][0] * (kernel + 1);
        for (auto w = kernel + 1; w < kernel_size; w++) {
            _data[w][kernel] += (*outImg)[h][w];
        }
        for (uint32_t w = kernel + 1; w < width - kernel; w++) {
            _data[h][w] = _data[h][w - 1] - (*outImg)[h][w - (kernel + 1)] + (*outImg)[h][w + kernel];
        }
    }
    for (auto h = 0; h < kernel; h++) {
        memcpy(_data[h], _data[kernel], width * sizeof(*_data[0]));
        memcpy(_data[height - 1 - h], _data[height - 1 - kernel], width * sizeof(*_data[0]));
    }
    for (uint32_t w = kernel; w < width - kernel; w++) {
        tmp = _data[kernel][w] * (kernel + 1);
        for (auto h = kernel + 1; h < kernel_size; h++) {
            tmp += _data[h][w];
        }
        (*outImg)[kernel][w] = (*second)[kernel][w] / sqrt(tmp);
        for (uint32_t h = kernel + 1; h < height - kernel; h++) {
            tmp = tmp - _data[h - (kernel + 1)][w] + _data[h + kernel][w];
//            outImg[h][w] = second[h][w] / sqrt(tmp / (kernel_size * kernel_size));
            (*outImg)[h][w] = (*second)[h][w] / sqrt(tmp);
        }
    }

    return outImg;
}

ImageSharedPtr ImageProcessor::subtraction(ImageSharedPtr const first,
                                            ImageSharedPtr const second)
{
    ImageSharedPtr outImg = ImageFactory::createImageFromImage(first);
    int32_t tmp = 0;
    for (uint32_t i = 0; i < first->getImageHeight() + first->getFrame() * 2; i++) {
        for (uint32_t j = 0; j < first->getImageWidth() + first->getFrame() * 2; j++) {
            tmp = (*first)[i][j] - (*second)[i][j];
            if (tmp < 0) {
                (*outImg)[i][j] = 0;
            } else {
                (*outImg)[i][j] = tmp;
            }
        }
    }
    return outImg;
}
