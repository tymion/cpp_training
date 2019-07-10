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
    //std::string rightFile = "resources/left.png";
    std::string rightFile = "resources/right.png";
    try {
        start = clock();
        ImageSharedPtr lImg = ImageFactory::createImageFromFile(leftFile);
        ImageFactory::createFileFromImage("test_outL.png", lImg);
        ImageSharedPtr rImg = ImageFactory::createImageFromFile(rightFile);
        ImageFactory::createFileFromImage("test_outR.png", rImg);
        ImageProcessor& proc = ImageProcessorFactory::createImageProcessor();
        ImageSharedPtr lGray = proc.changeColorSpace(lImg, ColorSpace::Grayscale);
        ImageFactory::createFileFromImage("test_grayL.png", lGray);
        ImageSharedPtr rGray = proc.changeColorSpace(rImg, ColorSpace::Grayscale);
        ImageFactory::createFileFromImage("test_grayR.png", rGray);
        uint8_t kernel = 5;
        ImageSharedPtr rG = proc.gaussian(rGray, kernel);
        ImageSharedPtr rLow = proc.lowPassFilter(rGray, kernel);
        ImageSharedPtr lLow = proc.lowPassFilter(lGray, kernel);
        lLow->fillFrames();
        rLow->fillFrames();
        ImageFactory::createFileFromImage("test_GausR.png", rG);
        ImageFactory::createFileFromImage("test_LowL.png", lLow);
        ImageFactory::createFileFromImage("test_LowR.png", rLow);
        ImageSharedPtr lSub = proc.subtraction(lGray, lLow);
        ImageSharedPtr rSub = proc.subtraction(rGray, rLow);
        ImageSharedPtr lDiff = proc.standardDeviation(lGray, lLow, kernel);
        ImageSharedPtr rDiff = proc.standardDeviation(rGray, rLow, kernel);
        ImageFactory::createFileFromImage("test_DiffL.png", lDiff);
        ImageFactory::createFileFromImage("test_DiffR.png", rDiff);
        ImageFactory::createFileFromImage("test_SubL.png", lSub);
        ImageFactory::createFileFromImage("test_SubR.png", rSub);
        ImageProcessorFactory::deleteImageProcessor(&proc);
        duration = (clock() - start) / (double) CLOCKS_PER_SEC;
        std::cout << "Time: "<< duration << std::endl;
    } catch (std::exception const &exc)
    {
        std::cerr << "Exception caught: " << exc.what() << std::endl;
        return -1;
    }
    return 0;
}
