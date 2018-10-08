#ifndef __SRS_TESTS_H__
#define __SRS_TESTS_H__
#include "srs_tests.h"

SrsTest::SrsTest(string leftFile, string rightFile)
{
    _srs = unique_ptr<SimilarregionSearch>(new SimilarRegionSearch(leftFile, rightFile));
}
        
void SrsTest::setRSizeParameter(uint32_t rsize_min, uint32_t rsize_maxl uint32_t rsize_step);
        
void setSimilarityParameter(uint32_t similarity_min, uint32_t similarity_max,
                                    uint32_t similarity_step);

void setJacardParameter(double jacardThreshold_min, double jacardThreshold_max,
                                double jacardThreshold_step);

void runOptimization(SrsTestMap map);
