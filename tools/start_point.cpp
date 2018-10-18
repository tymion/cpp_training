#include <string>
#include <cstring>
#include <exception>
#include <iostream>
#include <memory>
#include <ctime>
#include "srs_test.h"

#define rsize 9

void printHelp()
{
    std::cout << "\tstart_point - calculates starting point\n";
    std::cout << "\t\t\twhere values are lower then limit\n\n";
    std::cout << "\t-h --help  - print this help\n";
    std::cout << "\t-l [limit] - maximum value of region found for one origin region,\n";
    std::cout << "\t\t\tlimit should be positive value\n";
    std::cout << "\tE.g. ./start_point.out -l 520\n";
}

int main(int argc, char *argv[]) {
    clock_t start;
    double duration;
    std::string leftFile = "resources/left.png";
    std::string rightFile = "resources/left.png";
    if (argc != 3) {
        printHelp();
        return -1;
    }
    int32_t limit = atoi(argv[2]);
    if (strncmp(argv[1], "-l", 2) || limit <= 0) {
        printHelp();
        return -1;
    }
    try {
        SrsTest test(leftFile, rightFile);
        /*
        uint8_t maskData[rsize*rsize];
        memset(maskData, 1, sizeof(maskData));
        shared_ptr<Mask> mask(new Mask(rsize, rsize, maskData));
        */
        test.setSimilarityParameter(0, 255, 1);
        test.setJacardParameter(0, 1, 0.1);
        test.setPrecision(2, 0.01);
        test.setStartPointLimit(limit);
        uint32_t similarity = 0;
        double jacard = 0.0;
        start = clock();
        test.calcSrsStartPoint(similarity, jacard, rsize);
        duration = (clock() - start) / (double) CLOCKS_PER_SEC;
        std::cout << "Similarity: "<< similarity << " Jacard:" << jacard << std::endl;
        std::cout << "Time: "<< duration << std::endl;
    } catch (std::exception const &exc)
    {
        std::cerr << "Exception caught: " << exc.what() << std::endl;
        return -1;
    }
    return 0;
}
