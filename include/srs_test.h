#ifndef __SRS_TESTS_H__
#define __SRS_TESTS_H__
#include <memory>
#include <map>
#include "iimage.h"
#include "similar_region_search.h"

using namespace std;

typedef pair<uint32_t, double> SrsTestPair;
typedef std::map<uint32_t, SrsTestPair> SrsTestMap;

class SrsTest
{
    protected:
        uint32_t _rsize_min;
        uint32_t _rsize_max;
        uint32_t _rsize_step;
        uint32_t _similarity_min;
        uint32_t _similarity_max;
        uint32_t _similarity_step;
        double _jacardThreshold_min;
        double _jacardThreshold_max;
        double _jacardThreshold_step;
        unique_ptr<SimilarRegionSearch> _srs;

    public:
        SrsTest(shared_ptr<IImage>& lImage, shared_ptr<IImage>& rImage);
        SrsTest(string leftFile, string rightFile);

        void setRSizeParameter(uint32_t rsize_min, uint32_t rsize_max, uint32_t rsize_step);
        void setSimilarityParameter(uint32_t similarity_min, uint32_t similarity_max,
                                    uint32_t similarity_step);
        void setJacardParameter(double jacardThreshold_min, double jacardThreshold_max,
                                double jacardThreshold_step);
        void runOptimization(SrsTestMap& map);
};

#endif /*__SRS_TESTS_H__*/
