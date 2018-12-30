#pragma once
#include <cstdint>
#include <iostream>
#include <functional>

class IImage
{
    public:
        virtual uint32_t getHeight() = 0;
        virtual uint32_t getWidth() = 0;
        virtual bool getData(uint32_t row, uint8_t **data) = 0;
        virtual uint8_t getComponentSize() = 0;
        virtual uint8_t getComponentCnt() = 0;
        virtual void setDataProvider(std::function<uint8_t(uint32_t)> func) = 0;
        virtual ~IImage(){};
};
