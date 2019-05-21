#include "config.h"
#include <iostream>

double Configuration::getJacardThreshold()
{
    return Configuration::_jacardThreshold;
}

uint32_t Configuration::getSimilarityThreshold()
{
    return Configuration::_similarityThreshold;
}

std::string Configuration::toString()
{
    return "JacardThreshold:" + std::to_string(Configuration::_jacardThreshold) + ", similarityThreshold:" + std::to_string(Configuration::_similarityThreshold);
}
