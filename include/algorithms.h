#pragma once
#include <memory>
#include "mask.h"
#include "config.h"

template<typename T, typename S>
void grayscale_conversion(T **data, S **out, uint32_t height, uint32_t width)
{
    for (uint32_t i = 0; i < height; i++) {
        for (uint32_t j = 0; j < width; j++) {
            out[i][j] = data[i][j].gray();
        }
    }
}

template<typename T>
void low_pass_filter(T **data, T **out, uint32_t height, uint32_t width, uint32_t wsize)
{
    uint32_t kernel = wsize / 2;
    uint32_t i, j = 0;
    uint32_t tmp = 0;
    for (i = 0; i < kernel; i++) {
        for (j = 0; j < kernel; j++) {
            average(&(data[j]), out[j][i], kernel + j, 0, kernel + i, (kernel + j) * (kernel + i));
        }
    }
    for (i = kernel; i < width - kernel; i++) {
        for (j = 0; j < kernel; j++) {
            average(&(data[j]), out[j][i], kernel + j, i, wsize + i, (kernel + j) * wsize);
        }
    }
    for (i = width - kernel; i < width; i++) {
        for (j = 0; j < kernel; j++) {
            average(&(data[j]), out[j][i], kernel + j, i, wsize, (kernel + j) * (kernel + i));
        }
    }


    average(data, out[0, 0], kernel, kernel, kernel * kernel);
}

template<typename T>
void average(T **data, T &out, uint32_t height, uint32_t width_s, uint32_t width, uint32_t wsize)
{
    for (uint32_t i = 0; i < height; i++) {
        for (uint32_t j = width_s; j < width; j++) {
            out += data[i][j];
        }
    }
    out /= wsize;
}

template<typename T>
void average(T *data, T &out, uint32_t width)
{
    for (uint32_t j = 0; j < width; j++) {
        out += data[j];
    }
    out /= width;
}

template<typename T>
double count_index_jacarda(T **left, T **right, uint32_t height, uint32_t width)
{
    uint32_t similar = 0;

    uint32_t similarityThreshold = Configuration::getSimilarityThreshold();
    for (uint32_t i = 0; i < height; i++) {
        for (uint32_t j = 0; j < width; j++) {
            if ((left[i][j] - right[i][j]) < similarityThreshold) {
                similar++;
            }
        }
    }
    return (double) similar / (double) (height * width);
}

template<typename T>
double count_index_jacarda(T **left, T **right, uint32_t height, uint32_t width,
                            std::shared_ptr<Mask> const &mask)
{
    uint32_t similar = 0;

    uint32_t similarityThreshold = Configuration::getSimilarityThreshold();
    for (uint32_t i = 0; i < height; i++) {
        for (uint32_t j = 0; j < width; j++) {
            if (mask->getMask(i, j) == 0) {
                continue;
            }
            if ((left[i][j] - right[i][j]) < similarityThreshold) {
                similar++;
            }
        }
    }
    return (double) similar / (height * width);
}

template<typename T>
bool index_jacarda(T **left, T **right, uint32_t height, uint32_t width)
{
    return count_index_jacarda(left, right, height, width) >= Configuration::getJacardThreshold();
}

template<typename T>
bool index_jacarda(T **left, T **right, uint32_t height, uint32_t width,
                    std::shared_ptr<Mask> const &mask)
{
    return count_index_jacarda(left, right, height, width, mask) >= Configuration::getJacardThreshold();
}

template<typename T>
bool classic_compare(T **left, T **right, uint32_t height, uint32_t width,
                        std::shared_ptr<Mask> const &mask)
{
    for (uint32_t i = 0; i < height; i++) {
        for (uint32_t j = 0; j < width; j++) {
            if (mask->getMask(i, j) == 0) {
                continue;
            }
            if (left[i][j] != right[i][j]) {
                return false;
            }
        }
    }
    return true;
}

template<typename T>
bool classic_compare(T **left, T **right, uint32_t height, uint32_t width)
{
    for (uint32_t i = 0; i < height; i++) {
        for (uint32_t j = 0; j < width; j++) {
            if (left[i][j] != right[i][j]) {
                return false;
            }
        }
    }
    return true;
}
