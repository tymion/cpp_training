#include <string>
#include <exception>
#include <iostream>
#include "loader.hpp"

using namespace std;

//static void loadRow(IImage *image, uint8_t *data, uint32_t length) {
//    image->getData(data, length);
//}

int main() {
    string leftFile = "left.png";
    string rightFile = "right.png";
    try {
        Loader *loader = new Loader();
        IImage *lImage = loader->loadImage(leftFile);
        IImage *rImage = loader->loadImage(rightFile);
        delete lImage;
        delete rImage;
        delete loader;
    } catch (std::exception const &exc)
    {
        std::cerr << "Exception caught: " << exc.what() << std::endl;
        return -1;
    }
    return 0;
}
