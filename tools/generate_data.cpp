#include <string>
#include <cstring>
#include <exception>
#include <iostream>
#include <memory>
#include <ctime>
#include "srs_test.h"

void printHelp()
{
    std::cout << "\tgenerate_data - generate output data for given algorithm parameters\n\n";
    std::cout << "\t-h --help  - print this help\n";
    std::cout << "\t-s [similarity](int) - difference between points less then\n";
    std::cout << "\t\tsimilarity parameter classify point as similar,\n";
    std::cout << "\t-j [jacard](double) - TODO\n";
    std::cout << "\t-r [region_size](int) - TODO\n";
    std::cout << "\tE.g. ./generate_data.out -s 10 -j 0.8 -r 9\n";
}

int main(int argc, char *argv[]) {
    clock_t start;
    double duration;
    std::string leftFile = "resources/left.png";
    std::string rightFile = "resources/right.png";
    if (argc != 7) {
        printHelp();
        return -1;
    }
    int32_t similarity = 0;
    double jacard = 0.0;
    int32_t rsize = 0;
    for (int i = 1; i < 6; i++) {
        if (0 == strncmp(argv[i], "-s", 2)) {
            similarity = atoi(argv[++i]);
            if (similarity <= 0) {
                printHelp();
                return -1;
            }
        } else if (0 == strncmp(argv[i], "-j", 2)) {
            jacard = atof(argv[++i]);
            if (jacard <= 0.0) {
                printHelp();
                return -1;
            }
        } else if (0 == strncmp(argv[i], "-r", 2)) {
            rsize = atoi(argv[++i]);
            if (rsize <= 0) {
                printHelp();
                return -1;
            }
        } else {
            printHelp();
            return -1;
        }
    }
    try {
        std::cout << "Running with similarity:" << similarity << ", jacard:" << jacard;
        std::cout << ", rsize:" << rsize << std::endl;
        SrsTest test(leftFile, rightFile);
        /*
        uint8_t maskData[rsize*rsize];
        memset(maskData, 1, sizeof(maskData));
        shared_ptr<Mask> mask(new Mask(rsize, rsize, maskData));
        */
        test.setRSizeParameter(rsize, rsize, 1);
        test.setSimilarityParameter(1, similarity, 1);
        test.setJacardParameter(jacard, 1.0, 0.1);
        start = clock();
        test.generatesOutData("testoutput.txt");
        duration = (clock() - start) / (double) CLOCKS_PER_SEC;
        std::cout << "Time: "<< duration << std::endl;
    } catch (std::exception const &exc)
    {
        std::cerr << "Exception caught: " << exc.what() << std::endl;
        return -1;
    }
    return 0;
}
