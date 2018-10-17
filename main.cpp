#include <string>
#include <cstring>
#include <exception>
#include <iostream>
#include <memory>
#include <ctime>
#include "srs_test.h"

#define rsize 9

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
/*
        test.setSimilarityParameter(0, 255, 1);
        test.setJacardParameter(0, 1, 0.1);
        test.setPrecision(2, 0.01);
        test.setStartPointLimit(500 - rsize);
        uint32_t similarity = 0;
        double jacard = 0.0;
        start = clock();
        test.calcSrsStartPoint(similarity, jacard, rsize);
        duration = (clock() - start) / (double) CLOCKS_PER_SEC;
        std::cout << "Similarity: "<< similarity << " Jacard:" << jacard << std::endl;
        std::cout << "Time: "<< duration << std::endl;

        return 0;
*/
        test.setRSizeParameter(9, 9, 1);
        test.setSimilarityParameter(1, 105, 1);
        test.setJacardParameter(0.58, 1.0, 0.1);
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
