#include "srs_out_data.h"
#include <iostream>

SrsOutData::SrsOutData(uint32_t rsize, uint32_t similarity, double jacard)
{
    _rsize = rsize;
    _similarity = similarity;
    _jacard = jacard;
}

std::shared_ptr<RegionMapIterator> SrsOutData::createResult(uint32_t row, uint32_t col)
{
    auto pair =_map.emplace(std::piecewise_construct, std::forward_as_tuple(row, col),
                            std::forward_as_tuple());

    if (pair.second == false) {
        throw std::invalid_argument("Creating result has failed");
    }
    return std::make_shared<RegionMapIterator>(pair.first);
}

SrsOutData::~SrsOutData()
{
    clear();
}

void SrsOutData::addMatchedRegion(std::shared_ptr<RegionMapIterator> region, uint32_t row,
                                    uint32_t col, double similarity)
{
    (*region)->second.emplace_back(row, col, similarity);
}

void SrsOutData::clear()
{
    _map.clear();
}

bool SrsOutData::isOptimized()
{
    if (_map.size() == 0) {
        throw std::invalid_argument("Map has zero elements???!!!");
    }
    for (RegionMapIterator it = _map.begin(); it != _map.end(); ++it) {
        if (it->second.size() != 1) {
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
    for (RegionMapIterator it = _map.begin(); it != _map.end(); ++it) {
        if (it->second.size() > limit) {
            return true;
        }
    }
    return false;
}

void SrsOutData::printDataToFile(std::ofstream& file)
{
    file << "rsize:" << _rsize << ",similarity:" << _similarity << ",jacard:" << _jacard;
    file << ",map_size:" << _map.size() << std::endl;

    for (RegionMapIterator it = _map.begin(); it != _map.end(); it++) {
        file << "row:" << it->first.row << ",col:" << it->first.col;
        file << ",matched_cnt:" << it->second.size();
        for (auto itt = it->second.begin(); itt != it->second.end(); itt++) {
            file << ",row:" << (*itt).coordinates.row;
            file << ",col:" << (*itt).coordinates.col;
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
