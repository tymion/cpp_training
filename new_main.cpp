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
#define SAVE_IMG ImageFactory::createFileFromImage
#else
#define SAVE_IMG(file, image);
#endif


int main() {
    clock_t start;
    double duration;
    std::string leftFile = "resources/left.png";
    //std::string rightFile = "resources/left.png";
    std::string rightFile = "resources/right.png";
    try {
        start = clock();
        ImageSharedPtr lImg = ImageFactory::createImageFromFile(leftFile);
        SAVE_IMG("test_outL.png", lImg);
        ImageSharedPtr rImg = ImageFactory::createImageFromFile(rightFile);
        SAVE_IMG("test_outR.png", rImg);
        ImageProcessor& proc = ImageProcessorFactory::createImageProcessor();
        ImageSharedPtr lGray = proc.changeColorSpace(lImg, ColorSpace::Grayscale);
        SAVE_IMG("test_grayL.png", lGray);
        ImageSharedPtr rGray = proc.changeColorSpace(rImg, ColorSpace::Grayscale);
        SAVE_IMG("test_grayR.png", rGray);
        uint8_t kernel = 5;
        ImageSharedPtr rG = proc.gaussian(rGray, kernel);
        ImageSharedPtr rLow = proc.lowPassFilter(rGray, kernel);
        ImageSharedPtr lLow = proc.lowPassFilter(lGray, kernel);
        lLow->fillFrames();
        rLow->fillFrames();
        SAVE_IMG("test_GausR.png", rG);
        SAVE_IMG("test_LowL.png", lLow);
        SAVE_IMG("test_LowR.png", rLow);
        ImageSharedPtr lSub = proc.subtraction(lGray, lLow);
        ImageSharedPtr rSub = proc.subtraction(rGray, rLow);
        ImageSharedPtr lDiff = proc.standardDeviation(lGray, lLow, kernel);
        ImageSharedPtr rDiff = proc.standardDeviation(rGray, rLow, kernel);
        SAVE_IMG("test_DiffL.png", lDiff);
        SAVE_IMG("test_DiffR.png", rDiff);
        SAVE_IMG("test_SubL.png", lSub);
        SAVE_IMG("test_SubR.png", rSub);
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
