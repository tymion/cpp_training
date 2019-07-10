#pragma once

#include <cstdint>
#include <memory>
#include "matrix.h"

class Image : public Matrix<uint8_t>
{
    protected:
        uint32_t _height = 0;
        uint32_t _width = 0;
        uint8_t _frame = 0;
        uint8_t _component = 0;

    public:
        Image(uint32_t height, uint32_t width, uint8_t frame, uint8_t component,
                uint8_t **data);
        virtual ~Image();
        uint32_t getImageHeight() const;
        uint32_t getImageWidth() const;
        uint8_t getFrame() const;
        uint8_t getComponent() const;
        void fillFrames();
};

using ImageSharedPtr = std::shared_ptr<Image>;

template<size_t H, size_t W, size_t F, size_t C>
class StackImage : public Image
{
    private:
        uint8_t _stack_data[(H + 2*F)*(W + 2*F)*C] = {};
        uint8_t* _stack_tab[(H + 2*F)] = {};

    public:
        StackImage() : Image(H, W, F, C,
                                reinterpret_cast<uint8_t**>(&_stack_tab[0]))
        {
            for (uint32_t i = 0; i < H + 2*F; i++) {
                _stack_tab[i] = &_stack_data[i * (W + 2*F)*C];
            }
            LOG("Image %ld %ld %ld %ld %ld %ld\n", H, W, F, C, H+2*F, (W+2*F)*C);
        }
};
