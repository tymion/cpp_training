#pragma once
#include <list>
#include <map>
#include <ctime>

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
    public:
        SrsOutData();
        void clear();
        RegionCoordinates* createResult(uint32_t row, uint32_t col);
        void addMatchedRegion(RegionCoordinates* region, uint32_t row,
                                uint32_t col, double similarity);
        bool isOptimized();
        bool isUnderLimit(uint32_t limit);
};

/*
void FileDump(RegionMap& map)
{
    static struct tm *time = NULL;
    if (!time) {
        time_t time_val = time(0);
        time = gmtime(&time_val);
    }
}
*/