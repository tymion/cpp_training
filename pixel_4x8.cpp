#include <cstdlib>
#include <cstdint>
#include <pixel_4x8.h>

bool pixel_4x8::operator== (const pixel_4x8& pixel)
{
    if (_red != pixel._red ||
        _green != pixel._green ||
        _blue != pixel._blue) {
        return false;
    }
    return true;
}

bool pixel_4x8::operator!= (const pixel_4x8& pixel)
{
    if (_red != pixel._red ||
        _green != pixel._green ||
        _blue != pixel._blue) {
        return true;
    }
    return false;
}

pixel_4x8& pixel_4x8::operator- (const pixel_4x8& pixel)
{
    this->_red = abs(this->_red - pixel._red);
    this->_green = abs(this->_green - pixel._green);
    this->_blue = abs(this->_blue - pixel._blue);
    return *this;
}

//template <typename T>
bool pixel_4x8::operator> (const int value)
{
    if (_red > value and _green > value and _blue > value) {
        return true;
    }
    return false;
}
