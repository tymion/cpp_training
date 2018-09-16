#ifndef _REGION_H_
#define _REGION_H_
#include <cstring>
#include <iostream>
#include "mask.h"

using namespace std;

class RegionBase {
    public:
        virtual uint32_t getHeight() = 0;

        virtual uint32_t getWidth() = 0;

        virtual void setMask(Mask *mask) = 0;

        virtual void setData(uint32_t height, uint8_t *data) = 0;

        virtual void dataDump() = 0;

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

        void memNULLSet()
        {
            for (uint32_t i = 0; i < _height; i++) {
                _data[i] = NULL;
            }
        }

    public:
        Region(uint32_t height, uint32_t width, Mask *mask=NULL)
        {
            if (height == 0 || width == 0) {
                throw std::invalid_argument("Check input");
            }
            _height = height;
            _width = width;
            _mask = mask;
            _data = new T*[height];
            memNULLSet();
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

        void dataDump()
        {
#ifdef DEBUG
            for (uint32_t i = 0; i < _height && _data[i] != NULL; i++) {
                for (uint32_t j = 0; j < _width; j++) {
                    cout << _data[i][j];
                }
            }
#endif /* DEBUG */
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

            for (uint32_t i = 0; i < _height && _data[i] != NULL; i++) {
                for (uint32_t j = 0; j < _width; j++) {
                    if ((_mask && _mask->getMask(i, j) == 0)) {
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
            // TODO IF _data[0] == NULL we return true
            for (uint32_t i = 0; i < _height && _data[i] != NULL; i++) {
                for (uint32_t j = 0; j < _width; j++) {
                    if ((_mask && _mask->getMask(i, j) == 0)) {
                        continue;
                    }
//                    cout << ":" <<_data[i][j] << ":" << region._data[i][j] << endl;
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
