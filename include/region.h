#ifndef _REGION_H_
#define _REGION_H_
#include "mask.h"

class RegionBase {
    public:
        virtual uint32_t getHeight() = 0;

        virtual uint32_t getWidth() = 0;

        virtual void setMask(Mask *mask) = 0;

        virtual void setData(uint32_t height, uint8_t *data) = 0;

        virtual bool operator== (const RegionBase& region) = 0;

        virtual ~RegionBase() {};
};

template<typename T>
class Region : RegionBase {
    private:
        uint32_t _height;
        uint32_t _width;
        Mask *_mask;
        T **_data;

    public:
        Region(uint32_t height, uint32_t width, Mask *mask)
        {
            if (height == 0 || width == 0) {
                throw std::invalid_argument("Check input");
            }
            _height = height;
            _width = width;
            _mask = mask;
            _data = new T*[height];
        }

        Region(uint32_t height, uint32_t width)
        {
            if (height == 0 || width == 0) {
                throw std::invalid_argument("Check input");
            }
            _height = height;
            _width = width;
            _mask = NULL;
            _data = new T*[height];
        }

        virtual ~Region()
        {
            delete [] _data;
        }

        uint32_t getHeight()
        {
            return _height;
        }

        uint32_t getWidth()
        {
            return _width;
        }

        void setMask(Mask *mask)
        {
            _mask = mask;
        }

        void setData(uint32_t height, uint8_t *data)
        {
            _data[height] = (T*) data;
        }

        bool operator== (const RegionBase& region)
        {
            const Region<T>& regionT = (const Region<T>&)(region);
            return (*this) == regionT;
        }

        bool operator==(const Region<T>&  region)
        {
#ifdef INDEX_JACARDA
            uint32_t similar = 0;
            uint32_t different = 0;

            for (uint32_t i = 0; i < _height; i++) {
                for (uint32_t j = 0; j < _width; j++) {
                    if (_mask && _mask->getMask(i, j) == 0) {
                        continue;
                    }
                    if ((_data[i][j] - region._data[i][j]) < similarityThreshold) {
                        similar++;
                    } else {
                        different++;
                    }
                }
            }
            return similar / (similar + different) < jacardThreshold;
#else
            for (uint32_t i = 0; i < _height; i++) {
                for (uint32_t j = 0; j < _width; j++) {
                    if (_mask && _mask->getMask(i, j) == 0) {
                        continue;
                    }
                    if (_data[i][j] != region._data[i][j]) {
                        return false;
                    }
                }
            }
            return true;
#endif
        }

};
#endif /* _REGION_H_ */
