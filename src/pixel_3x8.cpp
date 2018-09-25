#include <cstdlib>
#include <pixel_3x8.h>

bool pixel_3x8::operator== (const pixel_3x8& pixel)
{
    if (_red != pixel._red ||
        _green != pixel._green ||
        _blue != pixel._blue) {
        return false;
    }
    return true;
}

bool pixel_3x8::operator!= (const pixel_3x8& pixel)
{
    if (_red != pixel._red ||
        _green != pixel._green ||
        _blue != pixel._blue) {
        return true;
    }
    return false;
}

pixel_3x8 pixel_3x8::operator- (const pixel_3x8& pixel)
{
    pixel_3x8 tmp(*this);
    tmp._red = abs(this->_red - pixel._red);
    tmp._green = abs(this->_green - pixel._green);
    tmp._blue = abs(this->_blue - pixel._blue);
    return tmp;
}

bool pixel_3x8::operator> (const int value)
{
    if (_red > value and
        _green > value and
        _blue > value) {
        return true;
    }
    return false;
}

bool pixel_3x8::operator< (const int value)
{
    if (_red < value and
        _green < value and
        _blue < value) {
        return true;
    }
    return false;
}

//std::ostream& pixel_3x8::operator<< (std::ostream& stream)
std::ostream & operator<< (std::ostream &stream, const pixel_3x8 &s)
{
    return (stream << std::hex << (int)s._red << (int)s._green << (int)s._blue << std::dec);
}
