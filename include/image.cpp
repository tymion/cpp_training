#pragma once
#include "image_file.h"
#include "image_storage_factory.h"

class Image {
    private:
        ImageFile *_imageFile;
        ImageStorage _storage;

    public:
        Image(ImageFile *file, ImageStorage &storage);
 
}
