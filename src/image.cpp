#include "image.h"
#include "storage.h"

Image::Image(std::string fileName)
{
    _file = std::unique_ptr<ImageFile>{ImageFileFactory::createImageFile(fileName)};
    _storage = std::unique_ptr<ImageStorage>{ImageStorageFactory::createImageStorage(_file->getHeight(), _file->getWidth())};
    Storage *storage = static_cast<Storage*> (_storage.get());

//    ImageStorage *storage_ptr = _storage.get();
//    auto callback = [storage_ptr] (uint32_t row) { return (storage_ptr)[row]; };
//    std::function<uint32_t* (uint32_t)> callback = [storage_ptr] (uint32_t row) { return (storage_ptr)[row]; };
    _file->loadImage(&Storage::getRow, storage);
}
