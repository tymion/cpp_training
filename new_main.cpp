#include <string>
#include <cstring>
#include <exception>
#include <iostream>
#include <memory>
#include <ctime>
#include "image_factory.h"
#include "image_processor_factory.h"
#include "color_space.h"

#define rsize 9

int main() {
    clock_t start;
    double duration;
    std::string leftFile = "resources/left.png";
    std::string rightFile = "resources/left.png";
    //std::string rightFile = "resources/right.png";
    try {
        start = clock();
        Configuration::setImageFrame(2);
        Image& lImg = ImageFactory::createImageFromFile(leftFile);
        Image& rImg = ImageFactory::createImageFromFile(rightFile);
        ImageProcessor& proc = ImageProcessorFactory::createImageProcessor();
        Image& gray = proc.changeColorSpace(lImg, ColorSpace::Grayscale);
        ImageFactory::createFileFromImage("test_gray.png", gray);
        Image& low = proc.lowPassFilter(gray, 5);
        low.fillFrames();
        ImageFactory::createFileFromImage("test_low.png", low);
        duration = (clock() - start) / (double) CLOCKS_PER_SEC;
        std::cout << "Time: "<< duration << std::endl;
    } catch (std::exception const &exc)
    {
        std::cerr << "Exception caught: " << exc.what() << std::endl;
        return -1;
    }
    return 0;
}
