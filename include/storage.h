#pragma once
#include <cstdint>

class Storage
{
    public:
        virtual uint8_t* getRow(uint32_t index) = 0;
        virtual ~Storage(){};
};
