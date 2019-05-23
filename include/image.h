#pragma once

#include <cstdint>

class Image
{
    protected:
        uint32_t _height = 0;
        uint32_t _width = 0;
        uint8_t _frame = 0;
        uint8_t _component = 0;
        uint8_t **_data = nullptr;

    public:
        Image(uint32_t height, uint32_t width, uint32_t frame, uint32_t component);
        virtual ~Image();
        uint32_t getHeight() const;
        uint32_t getWidth() const;
        uint8_t getFrame() const;
        uint8_t getComponent() const;
        void fillFrames();

        uint8_t* operator[](uint32_t index);
        uint8_t* operator[](uint32_t index) const;
};

template<size_t H, size_t W, size_t F, size_t C>
class StackImage : public Image
{
    private:
        uint8_t _stack_data[H + 2*F][(W + 2*F)*C] = {};

    public:
        StackImage() : Image(H, W, F, C)
        {
            Image::_data = reinterpret_cast<uint8_t**>(_stack_data);
        }
};


class HeapImage : public Image
{
    public:
        HeapImage(uint32_t height, uint32_t width, uint8_t frame,
                    uint8_t component, uint8_t **data) :
                    Image(height, width, frame, component)
        {
            Image::_data = data;
        }
};

