#ifndef __SRS_TESTS_H__
#define __SRS_TESTS_H__
#include <memory>
#include <map>

using namespace std;

typedef pair<uint32_t, double> SrsTestPair;
typedef std::map<uint32_t, SrsTestPair> SrsTestMap;

class SrsTest
{
    protected:
        unique_ptr<SimilarRegionSearch> _srs;
    public:
        SrsTest();
        void setRSizeParameter(uint32_t rsize_min, uint32_t rsize_maxl uint32_t rsize_step);
        void setSimilarityParameter(uint32_t similarity_min, uint32_t similarity_max,
                                    uint32_t similarity_step);
        void setJacardParameter(double jacardThreshold_min, double jacardThreshold_max,
                                double jacardThreshold_step);
        void runOptimization(SrsTestMap map);
};

#endif /*__SRS_TESTS_H__*/
