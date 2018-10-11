#ifndef _REGION_H_
#define _REGION_H_
#include <cstring>
#include <iostream>
#include <memory>
#include "mask.h"
#include "config.h"
#include "algorithms.h"

class RegionBase {
    public:
        virtual uint32_t getHeight() = 0;

        virtual uint32_t getWidth() = 0;

        virtual void setData(uint32_t height, uint8_t *data) = 0;

        virtual void dataDump() = 0;

        virtual bool compare(RegionBase& region, std::shared_ptr<Mask> const &mask, double &similarity) = 0;

        virtual bool compare(RegionBase& region, double &similarity) = 0;

        virtual void setMask(std::shared_ptr<Mask> const &mask) = 0;

        virtual bool operator== (const RegionBase& region) = 0;

        virtual ~RegionBase() {};
};

template<typename T>
class Region : RegionBase {
    private:
        uint32_t _height;
        uint32_t _width;
        std::shared_ptr<Mask> _mask;
        T **_data;

        void memNULLSet()
        {
            for (uint32_t i = 0; i < _height; i++) {
                _data[i] = NULL;
            }
        }

    public:
        Region(uint32_t height, uint32_t width, std::shared_ptr<Mask> const &mask=nullptr)
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

        void setMask(std::shared_ptr<Mask> const &mask)
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
                    std::cout << _data[i][j];
                }
                std::cout << std::endl;
            }
#endif /* DEBUG */
        }

        bool compare(RegionBase& region, std::shared_ptr<Mask> const &mask, double &similarity)
        {
            const Region<T>& regionT = (const Region<T>&)(region);
            similarity = count_index_jacarda(_data, regionT._data, _height, _width, mask);
            return similarity >= Configuration::getJacardThreshold();
        }

        bool compare(RegionBase& region, double &similarity)
        {
            const Region<T>& regionT = (const Region<T>&)(region);
            similarity = count_index_jacarda(_data, regionT._data, _height, _width);
            std::cout << "SubStep33:" << similarity << std::endl;
            return similarity >= Configuration::getJacardThreshold();
        }

        bool operator== (const RegionBase& region)
        {
            const Region<T>& regionT = (const Region<T>&)(region);
            return (*this) == regionT;
        }

        bool operator==(const Region<T>&  region)
        {
            if (_data[0] == NULL) {
                if (region._data[0] == NULL) {
                    // both regions are empty so we can assume they are equal
                    // we should check size also
                    // print log because we don't expect this sitution
                    std::cout << "Both regions are empty" << std::endl;
                    return true;
                }
                std::cout << "One region is empty" << std::endl;
                return false;
            }
#ifdef INDEX_JACARDA
            if (_mask) {
                return index_jacarda(_data, region._data, _height, _width, _mask);
            } else {
                return index_jacarda(_data, region._data, _height, _width);
            }
#else
            if (_mask) {
                return classic_compare(_data, region._data, _height, _width, _mask);
            } else {
                return classic_compare(_data, region._data, _height, _width);
            }
#endif
        }

};
#endif /* _REGION_H_ */
