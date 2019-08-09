#include <string>
#include <cstring>
#include <exception>
#include <iostream>
#include <memory>
#include <ctime>
#include "image_factory.h"
#include "image_processor_factory.h"
#include "color_space.h"

#ifdef DEBUG
#define SAVE_IMG(file, image); \
    if (image) { \
        ImageFactory::createFileFromImage(file, image); \
    }
#else
#define SAVE_IMG(file, image);
#endif


int main() {
    clock_t start;
    clock_t _start;
    double duration;
    std::string leftFile = "resources/left.png";
    //std::string rightFile = "resources/left.png";
    std::string rightFile = "resources/right.png";
    try {
        start = clock();
        _start = start;
        ImageSharedPtr lImg = ImageFactory::createImageFromFile(leftFile);
        SAVE_IMG("test_outL.png", lImg);
        ImageSharedPtr rImg = ImageFactory::createImageFromFile(rightFile);
        SAVE_IMG("test_outR.png", rImg);
        ImageProcessor& proc = ImageProcessorFactory::createImageProcessor();
        duration = (clock() - start) / (double) CLOCKS_PER_SEC;
        std::cout << "Time (start image processing): "<< duration << std::endl;
        start = clock();
        ImageSharedPtr lGray = proc.changeColorSpace(lImg, ColorSpace::Grayscale);
        duration = (clock() - start) / (double) CLOCKS_PER_SEC;
        std::cout << "Time (changeColorSpace): "<< duration << std::endl;
        lGray->fillFrames();
        start = clock();
        SAVE_IMG("test_grayL.png", lGray);
        ImageSharedPtr rGray = proc.changeColorSpace(rImg, ColorSpace::Grayscale);
        duration = (clock() - start) / (double) CLOCKS_PER_SEC;
        std::cout << "Time (changeColorSpace): "<< duration << std::endl;
        start = clock();
        SAVE_IMG("test_grayR.png", rGray);
        uint8_t kernel = 5;
        ImageSharedPtr rG = proc.gaussian(rGray, kernel);
        duration = (clock() - start) / (double) CLOCKS_PER_SEC;
        std::cout << "Time (gaussian): "<< duration << std::endl;
        start = clock();
        ImageSharedPtr rLow = proc.lowPassFilter(rGray, kernel);
        duration = (clock() - start) / (double) CLOCKS_PER_SEC;
        std::cout << "Time (lowPass): "<< duration << std::endl;
        start = clock();
        ImageSharedPtr lLow = proc.lowPassFilter(lGray, kernel);
        duration = (clock() - start) / (double) CLOCKS_PER_SEC;
        std::cout << "Time (lowPass): "<< duration << std::endl;
        start = clock();
        ImageSharedPtr rG7 = proc.gaussian(rGray, kernel);
        duration = (clock() - start) / (double) CLOCKS_PER_SEC;
        std::cout << "Time (gaussian): "<< duration << std::endl;
        start = clock();
        ImageSharedPtr rSubG = proc.subtraction(rG, rG7);
        duration = (clock() - start) / (double) CLOCKS_PER_SEC;
        std::cout << "Time (subtraction): "<< duration << std::endl;
        start = clock();
        lLow->fillFrames();
        rLow->fillFrames();
        SAVE_IMG("test_GausR.png", rG);
        SAVE_IMG("test_GausR7.png", rG7);
        SAVE_IMG("test_LowL.png", lLow);
        SAVE_IMG("test_LowR.png", rLow);
        ImageSharedPtr lSub = proc.subtraction(lGray, lLow);
        duration = (clock() - start) / (double) CLOCKS_PER_SEC;
        std::cout << "Time (subtraction): "<< duration << std::endl;
        start = clock();
        ImageSharedPtr rSub = proc.subtraction(rGray, rLow);
        duration = (clock() - start) / (double) CLOCKS_PER_SEC;
        std::cout << "Time (subtraction): "<< duration << std::endl;
        start = clock();
        ImageSharedPtr lDiff = proc.standardDeviation(lGray, lLow, kernel);
        duration = (clock() - start) / (double) CLOCKS_PER_SEC;
        std::cout << "Time (standardDeviation): "<< duration << std::endl;
        start = clock();
        ImageSharedPtr rDiff = proc.standardDeviation(rGray, rLow, kernel);
        duration = (clock() - start) / (double) CLOCKS_PER_SEC;
        std::cout << "Time (standardDeviation): "<< duration << std::endl;
        start = clock();
        SAVE_IMG("test_DiffL.png", lDiff);
        SAVE_IMG("test_DiffR.png", rDiff);
        SAVE_IMG("test_SubL.png", lSub);
        SAVE_IMG("test_SubR.png", rSub);
        ImageProcessorFactory::deleteImageProcessor(&proc);
        duration = (clock() - _start) / (double) CLOCKS_PER_SEC;
        std::cout << "Time: "<< duration << std::endl;
    } catch (std::exception const &exc)
    {
        std::cerr << "Exception caught: " << exc.what() << std::endl;
        return -1;
    }
    return 0;
}
