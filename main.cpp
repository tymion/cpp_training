#include <string>
#include <cstring>
#include <exception>
#include <iostream>
#include <memory>
#include <ctime>
#include "region.h"
#include "loader.h"
#include "region_factory.h"
#include "region_coordinates.h"
#include "similar_region_search.h"

using namespace std;

#define rsize 7

int main() {
    clock_t start;
    double duration;
    string leftFile = "resources/left.png";
    //string rightFile = "resources/left.png";
    string rightFile = "resources/right.png";
    try {
        unique_ptr<SimilarRegionSearch> srs(new SimilarRegionSearch(leftFile, rightFile));
        /*
        uint8_t maskData[rsize*rsize];
        memset(maskData, 1, sizeof(maskData));
        shared_ptr<Mask> mask(new Mask(rsize, rsize, maskData));
        */
        uint32_t similarity = 1;
        double jacard = 0.5;
        start = clock();
        RegionMap map;
        srs->search(rsize, similarity, jacard, mask, map);
        duration = (clock() - start) / (double) CLOCKS_PER_SEC;
        cout << "Time: "<< duration << endl;
        cout << "Coordinates:" << map.size() << endl;
    } catch (exception const &exc)
    {
        cerr << "Exception caught: " << exc.what() << endl;
        return -1;
    }
    return 0;
}
