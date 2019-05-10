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
        Configuration::setImageFrame(2);
        Configuration::setStorageSize(10);
        Image& lImg = ImageFactory::createImageFromFile(leftFile);
        Image& rImg = ImageFactory::createImageFromFile(rightFile);
        ImageProcessor& proc = ImageProcessorFactory::createImageProcessor();
        Image& lGray = proc.changeColorSpace(lImg, ColorSpace::Grayscale);
        Image& rGray = proc.changeColorSpace(rImg, ColorSpace::Grayscale);
        ImageFactory::deleteImage(&lImg);
        ImageFactory::deleteImage(&rImg);
        uint8_t kernel = 5;
        Image& rLow = proc.lowPassFilter(rGray, kernel);
        Image& lLow = proc.lowPassFilter(lGray, kernel);
        ImageFactory::createFileFromImage("test_LowR.png", rLow);
        ImageFactory::createFileFromImage("test_grayL.png", lGray);
        ImageFactory::createFileFromImage("test_grayR.png", rGray);
        ImageFactory::createFileFromImage("test_LowL.png", lLow);
        lLow.fillFrames();
        rLow.fillFrames();
        Image& lSub = proc.subtraction(lGray, lLow);
        Image& rSub = proc.subtraction(rGray, rLow);
        Image& lDiff = proc.standardDeviation(lGray, lLow, kernel);
        Image& rDiff = proc.standardDeviation(rGray, rLow, kernel);
        ImageFactory::createFileFromImage("test_DiffL.png", lDiff);
        ImageFactory::createFileFromImage("test_DiffR.png", rDiff);
        ImageFactory::createFileFromImage("test_SubL.png", lSub);
        ImageFactory::createFileFromImage("test_SubR.png", rSub);
        ImageFactory::deleteImage(&lGray);
        ImageFactory::deleteImage(&rGray);
        ImageFactory::deleteImage(&lLow);
        ImageFactory::deleteImage(&rLow);
        ImageFactory::deleteImage(&lDiff);
        ImageFactory::deleteImage(&rDiff);
        ImageFactory::deleteImage(&lSub);
        ImageFactory::deleteImage(&rSub);
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
