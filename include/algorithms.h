#ifndef _ALGORITHMS_H_
#define _ALGORITHMS_H_
#include "mask.h"
#include "config.h"

template<typename T>
double count_index_jacarda(T **left, T **right, uint32_t height, uint32_t width)
{
    uint32_t similar = 0;
    uint32_t different = 0;

    uint32_t similarityThreshold = Configuration::getSimilarityThreshold();
    for (uint32_t i = 0; i < height; i++) {
        for (uint32_t j = 0; j < width; j++) {
            if ((left[i][j] - right[i][j]) < similarityThreshold) {
                similar++;
            } else {
                different++;
            }
        }
    }
    return similar / (similar + different);
}

template<typename T>
double count_index_jacarda(T **left, T **right, uint32_t height, uint32_t width, Mask *mask)
{
    uint32_t similar = 0;
    uint32_t different = 0;

    uint32_t similarityThreshold = Configuration::getSimilarityThreshold();
    for (uint32_t i = 0; i < height; i++) {
        for (uint32_t j = 0; j < width; j++) {
            if (mask->getMask(i, j) == 0) {
                continue;
            }
            if ((left[i][j] - right[i][j]) < similarityThreshold) {
                similar++;
            } else {
                different++;
            }
        }
    }
    return similar / (similar + different);
}

template<typename T>
bool index_jacarda(T **left, T **right, uint32_t height, uint32_t width)
{
    return count_index_jacarda(left, right, height, width) >= Configuration::getJacardThreshold();
}

template<typename T>
bool index_jacarda(T **left, T **right, uint32_t height, uint32_t width, Mask *mask)
{
    return count_index_jacarda(left, right, height, width, mask) >= Configuration::getJacardThreshold();
}
#endif /* _ALGORITHMS_H_ */
