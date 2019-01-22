#pragma once
#include <memory>
#include "image_file.h"
#include "image_file_factory.h"
#include "image_storage_factory.h"

class Image {
    private:
        std::unique_ptr<ImageFile> _file;
        ImageStorage& _storage;

    public:
        Image(std::string fileName);
};
