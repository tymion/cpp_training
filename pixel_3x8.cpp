#include <cmath>
#include <pixel_3x8.h>

bool pixel_3x8::operator== (const pixel& pixel)
{
    const pixel_3x8 *tmp = dynamic_cast<const pixel_3x8*>(&pixel);
    if (_red != tmp->_red ||
        _green != tmp->_green ||
        _blue != tmp->_blue) {
        return false;
    }
    return true;
}

bool pixel_3x8::operator!= (const pixel& pixel)
{
    const pixel_3x8 *tmp = dynamic_cast<const pixel_3x8*>(&pixel);
    if (_red != tmp->_red ||
        _green != tmp->_green ||
        _blue != tmp->_blue) {
        return true;
    }
    return false;
}

pixel& pixel_3x8::operator- (const pixel& pix)
{
    const pixel_3x8 *tmp_pix = dynamic_cast<const pixel_3x8*>(&pix);
    this->_red = std::abs(this->_red - tmp_pix->_red);
    this->_green = std::abs(this->_green - tmp_pix->_green);
    this->_blue = std::abs(this->_blue - tmp_pix->_blue);
    return (pixel&) *this;
}

//template <typename T>
bool pixel_3x8::operator> (const int value)
{
    if (_red > value and
        _green > value and
        _blue > value) {
        return true;
    }
    return false;
}
