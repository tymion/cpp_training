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
        std::shared_ptr<ImageFile> lFile = ImageFileFactory::createImageFile(leftFile);
        std::shared_ptr<ImageFile> rFile = ImageFileFactory::createImageFile(rightFile);
        ImageStorage lImageStorage = ImageStorageFactory::createImageStorage(lImage->getHeight(), lImage->getWidth());
        ImageStorage rImageStorage = ImageStorageFactory::createImageStorage(rImage->getHeight(), rImage->getWidth());

        Image lImage = new Image(lFile, lImageStorage);
        Image rImage= new Image(rFile, rImageStorage);
        duration = (clock() - start) / (double) CLOCKS_PER_SEC;
        std::cout << "Time: "<< duration << std::endl;
    } catch (std::exception const &exc)
    {
        std::cerr << "Exception caught: " << exc.what() << std::endl;
        return -1;
    }
    return 0;
}
