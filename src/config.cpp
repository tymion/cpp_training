#include "config.h"

void Configuration::setJacardThreshold(double new_threshold)
{
    _jacardThreshold = new_threshold;
}

double Configuration::getJacardThreshold()
{
    return _jacardThreshold;
}

void Configuration::setSimilarityThreshold(uint32_t new_threshold)
{
    _similarityThreshold = new_threshold;
}

uint32_t Configuration::getSimilarityThreshold()
{
    return _similarityThreshold;
}
