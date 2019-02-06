#include "image_processor_factory.h"

Image& ImageProcessor::changeColorSpace(Image const& img, ColorSpace color)
{
    ImageFactory::createImageFromImage(img, color);
}
