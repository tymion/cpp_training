#include "config.h"
#include <iostream>

std::string Configuration::toString()
{
    return "JacardThreshold:" + std::to_string(Configuration::_jacardThreshold) + ", similarityThreshold:" + std::to_string(Configuration::_similarityThreshold);
}
