#include "srs_out_data.h"

SrsOutData::SrsOutData()
{
}

RegionCoordinates& SrsOutData::createResult(uint32_t row, uint32_t col)
{
    RegionCoordinates* reg = (RegionCoordinates*) malloc(sizeof(struct region_coordinates_));
    reg->row = row;
    reg->col = col;
    _map[reg] = new RegionMatchedList();
    return *reg;
}

void SrsOutData::addMatchedRegion(RegionCoordinates& region, uint32_t row,
                                    uint32_t col, double similarity)
{
    if (!_map[&region]) {
        throw std::invalid_argument("Invalid region");
    }
    RegionMatched* matched = new RegionMatched();
    matched->coordinated.row = row;
    matched->coordinated.col = col;
    matched->similarity_degree = similarity;
    _map[&region]->push_back(matched);
}
