#include <string>
#include <cstring>
#include <exception>
#include <iostream>
#include <memory>
#include <ctime>
#include "srs_test.h"

using namespace std;

#define rsize 7

int main() {
    clock_t start;
    double duration;
    string leftFile = "resources/left.png";
    string rightFile = "resources/left.png";
    //string rightFile = "resources/right.png";
    try {
        SrsTest test(leftFile, rightFile);
        /*
        uint8_t maskData[rsize*rsize];
        memset(maskData, 1, sizeof(maskData));
        shared_ptr<Mask> mask(new Mask(rsize, rsize, maskData));
        */
        test.setRSizeParameter(3, 9, 1);
        test.setSimilarityParameter(10, 25, 1);
        test.setJacardParameter(0.5, 0.9, 0.1);
        start = clock();
        SrsTestMap map;
        test.runOptimization(map);
        duration = (clock() - start) / (double) CLOCKS_PER_SEC;
        cout << "Time: "<< duration << endl;
        for (SrsTestMap::iterator it = map.begin(); it != map.end(); ++it) {
            cout << "rsize:" << it->first << ", simili:" << it->second.first << ", jacard:" << it->second.second << endl;
        }
        cout << "Coordinates:" << map.size() << endl;
    } catch (exception const &exc)
    {
        cerr << "Exception caught: " << exc.what() << endl;
        return -1;
    }
    return 0;
}
