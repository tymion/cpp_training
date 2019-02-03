#pragma once
#include <cstdint>
#include <iostream>
#include <functional>

class ImageFile
{
    public:
        virtual uint32_t getHeight() = 0;
        virtual uint32_t getWidth() = 0;
        virtual bool loadImage(std::function<uint8_t* (uint32_t)> getRowCallback) = 0;
        virtual uint8_t getComponentSize() = 0;
        virtual uint8_t getComponentCnt() = 0;
        virtual ~ImageFile(){};
};
