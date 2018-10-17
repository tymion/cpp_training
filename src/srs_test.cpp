#include "srs_out_data.h"
#include "srs_test.h"
#include <fstream>

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

void SrsTest::setPrecision(uint32_t similarity, double jacard)
{
    _similarityPrecision = similarity;
    _jacardPrecision = jacard;
}

void SrsTest::setStartPointLimit(uint32_t limit)
{
    _startPointLimit = limit;
}

SrsParam SrsTest::quickSearch(uint32_t rsize, uint32_t similarity_min, uint32_t similarity_max,
                            double jacard_min, double jacard_max)
{
    double jacardDiv = (jacard_max - jacard_min) / 2;
    uint32_t similarityDiv = (similarity_max - similarity_min) / 2;

    if (similarityDiv < _similarityPrecision || jacardDiv < _jacardPrecision) {
        return { similarity_min + similarityDiv, jacard_min + jacardDiv };
    }

    std::cout << "Run simi:" << similarity_min + similarityDiv << " jaca:" << jacard_min + jacardDiv << "\n";
    SrsOutData data(rsize, similarity_min + similarityDiv, jacard_min + jacardDiv);
    _srs->search(rsize, similarity_min + similarityDiv, jacard_min + jacardDiv, data);
    if (data.isUnderLimit(_startPointLimit)) {
        data.clear();
        return quickSearch(rsize, similarity_min, similarity_min + similarityDiv,
                            jacard_min + jacardDiv, jacard_max);
    } else {
        data.clear();
        return quickSearch(rsize, similarity_min + similarityDiv, similarity_max,
                            jacard_min, jacard_min + jacardDiv);
    }
}

void SrsTest::calcSrsStartPoint(uint32_t &similarity, double &jacard, uint32_t rsize)
{
    SrsParam ret = quickSearch(rsize, _similarity_min, _similarity_max, _jacardThreshold_min,
                                _jacardThreshold_max);
    similarity = ret.similarity;
    jacard = ret.jacard;
}

void SrsTest::generatesOutData(std::string filename)
{
    uint32_t i = 0;
    double j = 0.0;
    std::ofstream file(filename);
    for (uint32_t r = _rsize_min; r <= _rsize_max; r +=_rsize_step) {
        for (i = _similarity_max; i >= _similarity_min; i -= _similarity_step) {
            for (j = _jacardThreshold_min; j <= _jacardThreshold_max; j += _jacardThreshold_step) {
                SrsOutData data(r, i, j);
                _srs->search(r, i, j, data);
                data.printDataToFile(file);
                data.clear();
            }
        }
    }
    file.close();
}

void SrsTest::runOptimization(SrsTestMap& map)
{
    uint32_t i = 0;
    double j = 0.0;
    for (uint32_t r = _rsize_min; r <= _rsize_max; r +=_rsize_step) {
        bool found = false;
        for (i = _similarity_max; i >= _similarity_min; i -= _similarity_step) {
            for (j = _jacardThreshold_min; j <= _jacardThreshold_max; j += _jacardThreshold_step) {
                std::cout << "==" << r << "==" << i << "==" << j << "\n";
                found = false;
                SrsOutData data(r, i, j);
                _srs->search(r, i, j, data);
                found = data.isOptimized();
                if (found) {
                    break;
                }
            }
            if (found) {
                break;
            }
        }
        if (found) {
            map[r] = SrsTestPair(i, j);
        } else {
            throw std::invalid_argument("No 1 to 1 found???!!!");
        }
    }
}
