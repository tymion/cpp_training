#include <string.h>
#include "image.h"
#include "storage.h"

Image::Image(std::string fileName)
{
    _file = std::unique_ptr<ImageFile>{ImageFileFactory::createImageFile(fileName)};
    _storage = std::unique_ptr<ImageStorage>{ImageStorageFactory::createImageStorage(_file->getHeight(), _file->getWidth())};
    ImageStorage &storage = static_cast<ImageStorage&> (*_storage);

    auto callback = [&storage] (uint32_t row) { return storage[storage.getFrame() + row] + storage.getFrame(); };
    _file->loadImage(callback);
    for (auto i = 0; i < _storage->getFrame(); i++) {
        memcpy(storage[i], storage[_storage->getFrame()], storage.getWidth());
        memcpy(storage[storage.getHeight() + i], storage[_storage->getFrame() + storage.getHeight() - 1], storage.getWidth());
    }
    for (auto i = 0; i < storage.getHeight() + 2 * storage.getFrame(); i++) {
        for (auto j = 0; j < storage.getFrame(); j++) {
            storage[i][j] = storage[i][storage.getFrame()];
            storage[i][storage.getFrame() + storage.getWidth() + j] = storage[i][storage.getFrame() + storage.getHeight()];
        }
    }
}
