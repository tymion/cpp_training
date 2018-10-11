#include "region_coordinates.h"
#include "srs_test.h"

SrsTest::SrsTest(std::shared_ptr<IImage>& lImage, std::shared_ptr<IImage>& rImage)
{
    _srs = std::unique_ptr<SimilarRegionSearch>(new SimilarRegionSearch(lImage, rImage));
}
        
SrsTest::SrsTest(std::string leftFile, std::string rightFile)
{
    _srs = std::unique_ptr<SimilarRegionSearch>(new SimilarRegionSearch(leftFile, rightFile));
}
        
void SrsTest::setRSizeParameter(uint32_t rsize_min, uint32_t rsize_max, uint32_t rsize_step)
{
    _rsize_min = rsize_min;
    _rsize_max = rsize_max;
    _rsize_step = rsize_step;
}
        
void SrsTest::setSimilarityParameter(uint32_t similarity_min, uint32_t similarity_max,
                                        uint32_t similarity_step)
{
    _similarity_min = similarity_min;
    _similarity_max = similarity_max;
    _similarity_step = similarity_step;
}

void SrsTest::setJacardParameter(double jacardThreshold_min, double jacardThreshold_max,
                                    double jacardThreshold_step)
{
    _jacardThreshold_min = jacardThreshold_min;
    _jacardThreshold_max = jacardThreshold_max;
    _jacardThreshold_step = jacardThreshold_step;
}

void SrsTest::runOptimization(SrsTestMap& map)
{
    RegionMap rmap;
    uint32_t i = 0;
    double j = 0.0;
    for (uint32_t r = _rsize_min; r <= _rsize_max; r +=_rsize_step) {
        bool found = false;
        for (i = _similarity_max; i >= _similarity_min; i -= _similarity_step) {
            for (j = _jacardThreshold_min; j <= _jacardThreshold_max; j += _jacardThreshold_step) {
                found = false;
                _srs->search(r, j, i, rmap);
                if (rmap.size() == 0) {
                    std::cout << "map size is zero???!!!r:" << r << ", j:" << j << ", i:" << i << std::endl;
                }
                for (RegionMap::iterator it = rmap.begin(); it != rmap.end(); ++it) {
                    if (it->second->size() == 0) {
                        throw std::invalid_argument("Zero size list in map???!!!");
                    } else if (it->second->size() != 1) {
                        found = true;
                        break;
                    }
                }
                if (!found) {
                    break;
                }
            }
            if (!found) {
                break;
            }
        }
        if (!found) {
            map[r] = SrsTestPair(i, j);
            for (RegionMap::iterator it = rmap.begin(); it != rmap.end(); ++it) {
                rmap.erase(it);
            }
        } else {
            throw std::invalid_argument("No 1 to 1 found???!!!");
        }
    }
}
