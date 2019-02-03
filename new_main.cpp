#include <string>
#include <cstring>
#include <exception>
#include <iostream>
#include <memory>
#include <ctime>
#include "image.h"
#include "image_file_factory.h"
#include "image_storage_factory.h"

#define rsize 9

int main() {
    clock_t start;
    double duration;
    std::string leftFile = "resources/left.png";
    std::string rightFile = "resources/left.png";
    //std::string rightFile = "resources/right.png";
    try {
        start = clock();
        Image *lImage = new Image(leftFile);
        Image *rImage= new Image(rightFile);
        duration = (clock() - start) / (double) CLOCKS_PER_SEC;
        std::cout << "Time: "<< duration << std::endl;
    } catch (std::exception const &exc)
    {
        std::cerr << "Exception caught: " << exc.what() << std::endl;
        return -1;
    }
    return 0;
}
