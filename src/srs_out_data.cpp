#include "srs_out_data.h"

SrsOutData::SrsOutData()
{
}

RegionCoordinates* SrsOutData::createResult(uint32_t row, uint32_t col)
{
    RegionCoordinates* reg = (RegionCoordinates*) malloc(sizeof(struct region_coordinates_));
    reg->row = row;
    reg->col = col;
    _map[reg] = new RegionMatchedList();
    return reg;
}

void SrsOutData::addMatchedRegion(RegionCoordinates* region, uint32_t row,
                                    uint32_t col, double similarity)
{
    if (!_map[region]) {
        throw std::invalid_argument("Invalid region");
    }
    RegionMatched* matched = new RegionMatched();
    matched->coordinates.row = row;
    matched->coordinates.col = col;
    matched->similarity_degree = similarity;
    _map[region]->push_back(matched);
}

bool SrsOutData::isOptimized()
{
    for (RegionMap::iterator it = _map.begin(); it != _map.end(); ++it) {
        if (it->second->size() == 0) {
            throw std::invalid_argument("Zero size list in map???!!!");
        } else if (it->second->size() != 1) {
            return false;
        }
    }
    return true;
}
