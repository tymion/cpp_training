#pragma once
#include <list>
#include <map>
#include <ctime>
#include <string>
#include <fstream>

struct region_coordinates_ {
    uint32_t row;
    uint32_t col;
};
typedef struct region_coordinates_ RegionCoordinates;

struct region_matched_ {
    struct region_coordinates_ coordinates;
    double similarity_degree;
};
typedef struct region_matched_ RegionMatched;

typedef std::list<RegionMatched*> RegionMatchedList;

typedef std::map<const RegionCoordinates*, RegionMatchedList*> RegionMap;

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

        RegionCoordinates* createResult(uint32_t row, uint32_t col);
        void addMatchedRegion(RegionCoordinates* region, uint32_t row,
                                uint32_t col, double similarity);

        bool isOptimized();
        bool isUnderLimit(uint32_t limit);
};
