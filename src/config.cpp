#include "config.h"
#include <iostream>

Configuration& Configuration::getInstance()
{
    static Configuration instance;
    return instance;
}

void Configuration::setJacardThreshold(double new_threshold)
{
    Configuration::getInstance()._jacardThreshold = new_threshold;
}

double Configuration::getJacardThreshold()
{
    return Configuration::getInstance()._jacardThreshold;
}

void Configuration::setSimilarityThreshold(uint32_t new_threshold)
{
    Configuration::getInstance()._similarityThreshold = new_threshold;
}

uint32_t Configuration::getSimilarityThreshold()
{
    return Configuration::getInstance()._similarityThreshold;
}

std::string Configuration::toString()
{
    return "JacardThreshold:" + std::to_string(Configuration::getInstance()._jacardThreshold) + ", similarityThreshold:" + std::to_string(Configuration::getInstance()._similarityThreshold);
}
