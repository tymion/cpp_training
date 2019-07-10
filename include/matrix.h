#pragma once

#include <cstdint>
#include "logger.h"

template<typename T>
class Matrix
{
    protected:
        uint32_t _height = 0;
        uint32_t _width = 0;
        T **_data = nullptr;

    public:
        Matrix(uint32_t height, uint32_t width, T** data) : _height(height),
                                                            _width(width),
                                                            _data(data) {}
        virtual ~Matrix()
        {
        }

        uint32_t getMatrixHeight() const
        {
            return _height;
        }

        uint32_t getMatrixWidth() const
        {
            return _width;
        }

        T* operator[](uint32_t index) const
        {
#ifdef DEBUG
            if (!_data) {
                LOG("_data is null\n");
            }
#endif
            return _data[index];
        }

        T* operator[](uint32_t index)
        {
#ifdef DEBUG
            if (!_data) {
                LOG("_data is null\n");
            }
#endif
            return _data[index];
        }
};
