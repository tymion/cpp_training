#include "image.h"

Image::Image(std::string fileName)
{
    _file = std::unique_ptr<ImageFile>{ImageFileFactory::createImageFile(fileName)};
    _storage = ImageStorageFactory::createImageStorage(_file->getHeight(), _file->getWidth());
}
