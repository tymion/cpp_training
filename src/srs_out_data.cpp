#include "srs_out_data.h"
#include <iostream>

SrsOutData::SrsOutData(uint32_t rsize, uint32_t similarity, double jacard)
{
    _rsize = rsize;
    _similarity = similarity;
    _jacard = jacard;
}

RegionCoordinates* SrsOutData::createResult(uint32_t row, uint32_t col)
{
    RegionCoordinates* reg = new RegionCoordinates();
    reg->row = row;
    reg->col = col;
    _map[reg] = new RegionMatchedList();
    return reg;
}

SrsOutData::~SrsOutData()
{
    clear();
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
    delete matched;
}

void SrsOutData::clear()
{
    for (RegionMap::iterator it = _map.begin(); it != _map.end(); ++it) {
        delete it->second;
        delete it->first;
    }
    _map.clear();
}

bool SrsOutData::isOptimized()
{
    if (_map.size() == 0) {
        throw std::invalid_argument("Map has zero elements???!!!");
    }
    for (RegionMap::iterator it = _map.begin(); it != _map.end(); ++it) {
        if (it->second->size() != 1) {
            return false;
        }
    }
    return true;
}

bool SrsOutData::isUnderLimit(uint32_t limit)
{
    if (_map.size() == 0) {
        throw std::invalid_argument("Map has zero elements???!!!");
    }
    for (RegionMap::iterator it = _map.begin(); it != _map.end(); ++it) {
        if (it->second->size() > limit) {
            return true;
        }
    }
    return false;
}

void SrsOutData::printDataToFile(std::ofstream& file)
{
    file << "rsize:" << _rsize << ",similarity:" << _similarity << ",jacard:" << _jacard << ",map_size:" << _map.size() << std::endl;

    for (RegionMap::iterator it = _map.begin(); it != _map.end(); ++it) {
        file << "row:" << it->first->row << ",col:" << it->first->col;
        file << ",matched_cnt:" << it->second->size();
        struct region_matched_ *tmp = NULL;
        if (it->second->begin() != it->second->end()) {
            tmp = *(it->second->begin());
            file << ",row::" << tmp->coordinates.row;
            file << ",col::" << tmp->coordinates.col;
        }
        file << std::endl;
    }
}

void SrsOutData::printDataToFile(std::string filename)
{
    std::ofstream file(filename, std::ios::app);
    printDataToFile(file);
    file.close();
}
