#ifndef __REGION_COORDINATES__
#define __REGION_COORDINATES__
#include <list>
#include <map>

struct region_coordinates_ {
    uint32_t row;
    uint32_t col;
};
#define RegionCoordinatesSize sizeof(region_coordinates_)
typedef struct region_coordinates_ * RegionCoordinates;

struct region_matched_ {
    struct region_coordinates_ coordinates;
    double similarity_degree;
};
typedef struct region_matched_ RegionMatched;

typedef std::list<RegionMatched*> RegionMatchedList;

typedef std::map<const RegionCoordinates, RegionMatchedList*> RegionMap;

#endif /*__REGION_COORDINATES__*/
