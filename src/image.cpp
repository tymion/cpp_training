#include "image.h"

Image::Image(std::string fileName)
{
    _file = std::unique_ptr<ImageFile>{ImageFileFactory::createImageFile(fileName)};
    _storage = std::unique_ptr<ImageStorage>{ImageStorageFactory::createImageStorage(_file->getHeight(), _file->getWidth())};
}
