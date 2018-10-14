#include <string>
#include <cstring>
#include <exception>
#include <iostream>
#include <memory>
#include <ctime>
#include "srs_test.h"

#define rsize 7

int main() {
    clock_t start;
    double duration;
    std::string leftFile = "resources/left.png";
    std::string rightFile = "resources/left.png";
    //std::string rightFile = "resources/right.png";
    try {
        SrsTest test(leftFile, rightFile);
        /*
        uint8_t maskData[rsize*rsize];
        memset(maskData, 1, sizeof(maskData));
        shared_ptr<Mask> mask(new Mask(rsize, rsize, maskData));
        */
        test.setRSizeParameter(9, 9, 1);
        test.setSimilarityParameter(1, 10, 1);
        test.setJacardParameter(0.7, 1.0, 0.1);
        start = clock();
        SrsTestMap map;
        test.runOptimization(map);
        duration = (clock() - start) / (double) CLOCKS_PER_SEC;
        std::cout << "Time: "<< duration << std::endl;
        for (SrsTestMap::iterator it = map.begin(); it != map.end(); ++it) {
            std::cout << "rsize:" << it->first << ", simili:" << it->second.first << ", jacard:" << it->second.second << std::endl;
        }
        std::cout << "Coordinates:" << map.size() << std::endl;
    } catch (std::exception const &exc)
    {
        std::cerr << "Exception caught: " << exc.what() << std::endl;
        return -1;
    }
    return 0;
}
