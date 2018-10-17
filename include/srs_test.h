#pragma once
#include <memory>
#include <map>
#include "iimage.h"
#include "similar_region_search.h"

typedef std::pair<uint32_t, double> SrsTestPair;
typedef std::map<uint32_t, SrsTestPair> SrsTestMap;

struct SrsParam {
    uint32_t similarity;
    double jacard;
};

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

        double _jacardPrecision;
        uint32_t _similarityPrecision;

        uint32_t _startPointLimit;

        std::unique_ptr<SimilarRegionSearch> _srs;

    public:
        SrsTest(std::shared_ptr<IImage>& lImage, std::shared_ptr<IImage>& rImage);
        SrsTest(std::string leftFile, std::string rightFile);

        void setRSizeParameter(uint32_t rsize_min, uint32_t rsize_max, uint32_t rsize_step);

        void setSimilarityParameter(uint32_t similarity_min,
                                    uint32_t similarity_max,
                                    uint32_t similarity_step);

        void setJacardParameter(double jacardThreshold_min, double jacardThreshold_max,
                                double jacardThreshold_step);

        void setPrecision(uint32_t similarity, double jacard);

        void setStartPointLimit(uint32_t limit);

        void generatesOutData(std::string filename);

        SrsParam quickSearch(uint32_t rsize, uint32_t similarity_min, uint32_t similarity_max,
                            double jacard_min, double jacard_max);

        void calcSrsStartPoint(uint32_t &similarity, double &jacard, uint32_t rsize);

        void runOptimization(SrsTestMap& map);
};
