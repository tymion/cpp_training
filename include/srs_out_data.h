#pragma once
#include <list>
#include <map>
#include <ctime>
#include <string>
#include <fstream>
#include <memory>

struct region_coordinates_ {
    uint32_t row;
    uint32_t col;
    region_coordinates_(uint32_t row, uint32_t col)
        : row(row), col(col) {
    };
    bool operator<(const region_coordinates_& reg) const {
        if (this->row < reg.row || (this->row == reg.row && this->col < reg.col)) {
            return true;
        }
        return false;
    }
};
typedef struct region_coordinates_ RegionCoordinates;

struct region_matched_ {
    struct region_coordinates_ coordinates;
    double similarity_degree;
    region_matched_(uint32_t row, uint32_t col, double similarity)
        : coordinates{row, col}, similarity_degree(similarity) {
    };
};
typedef struct region_matched_ RegionMatched;

typedef std::list<RegionMatched> RegionMatchedList;

typedef std::map<const RegionCoordinates, RegionMatchedList> RegionMap;
typedef RegionMap::iterator RegionMapIterator;

class SrsOutData
{
    protected:
        RegionMap _map;

        uint32_t _rsize;
        uint32_t _similarity;
        double _jacard;

    public:
        SrsOutData(uint32_t rsize, uint32_t similarity, double jacard);
        ~SrsOutData();

        void clear();
        void printDataToFile(std::string filename);
        void printDataToFile(std::ofstream& file);

        std::shared_ptr<RegionMapIterator> createResult(uint32_t row, uint32_t col);
        void addMatchedRegion(std::shared_ptr<RegionMapIterator> region, uint32_t row,
                                uint32_t col, double similarity);

        bool isOptimized();
        bool isUnderLimit(uint32_t limit);
};
