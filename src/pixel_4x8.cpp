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

pixel_4x8 pixel_4x8::operator- (const pixel_4x8& pixel)
{
    pixel_4x8 tmp(*this);
    tmp._red = abs(this->_red - pixel._red);
    tmp._green = abs(this->_green - pixel._green);
    tmp._blue = abs(this->_blue - pixel._blue);
    return tmp;
}

//template <typename T>
bool pixel_4x8::operator> (const int value)
{
    if (_red > value and _green > value and _blue > value) {
        return true;
    }
    return false;
}

bool pixel_4x8::operator< (const int value)
{
    if (_red < value and _green < value and _blue < value) {
        return true;
    }
    return false;
}

//std::ostream& pixel_4x8::operator<< (std::ostream& stream)
std::ostream & operator<< (std::ostream &stream, const pixel_4x8 &s)
{
    stream << std::hex << (int)s._red << (int)s._green << (int)s._blue << (int)s._alpha << std::dec << std::endl;
    return stream;
}

uint32_t pixel_4x8::gray()
{
#ifdef GRAYSCALE_CONVERSION_AVERAGE
    return ((uint32_t) this._reg + this._green + this._blue) / 3 ;
#elif GRAYSCALE_CONVERSION_BT_709
    return ((float) this._reg * 0.2126 + (float) this._green * 0.7152 + (float) this._blue * 0.0722);
#elif GRAYSCALE_CONVERSION_BT_601
    return ((float) this._reg * 0.299 + (float) this._green * 0.587 + (float) this._blue * 0.114);
#endif
    return 0;
}
