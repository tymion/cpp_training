#ifndef _REGION_HPP_
#define _REGION_HPP_

class Region {
    private:
        uint32_t _height;
        uint32_t _width;
        uint8_t **data;

    public:
        Region(uint32_t height, uint32_t width);

        uint32_t getHeight();
        void setHeight(uint32_t height);

        uint32_t getWidth();
        void setWidth(uint32_t width);

};
#endif /* _REGION_HPP_ */
