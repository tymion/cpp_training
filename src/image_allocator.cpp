#include "image_allocator.h"

ImageSharedPtr
ImageAllocator::allocate(uint32_t height, uint32_t width, uint8_t frame,
                            uint8_t component)
{
    void* ptr = nullptr;
    if (Conf::getImageHeight() == height && Conf::getImageFrame() == frame) {
        if (max_width * 3 == (width + 2 * frame) * component) {
            if ((ptr = stackImageBigAlloc.allocate()) == nullptr) {
                return nullptr;
            }
            return ImageSharedPtr(new (ptr) StackImageBig(), [=](Image* img)
                        {
                            img->~Image();
                            stackImageBigAlloc.deallocate(img);
                        });
        } else if (max_width * 1 == (width + 2 * frame) * component) {
            if ((ptr = stackImageSmallAlloc.allocate()) == nullptr) {
                return nullptr;
            }
            return ImageSharedPtr(new (ptr) StackImageSmall(), [=](Image* img)
                        {
                            img->~Image();
                            stackImageSmallAlloc.deallocate(img);
                        });
        }
    } else {
        uint8_t **ptr_data = static_cast<uint8_t**>(alloc.allocate(height + 2 * frame * sizeof(uint8_t*)).ptr);
        uint8_t *tmp = static_cast<uint8_t*>(alloc.allocate((height + 2 * frame) *
                                                        (width + 2 * frame) * component).ptr);
        if ((ptr = imageAlloc.allocate()) == nullptr || ptr_data == nullptr || tmp == nullptr) {  
            return nullptr;
        }
        for (uint8_t i = 0; i < height + 2 * frame; i++) {
            ptr_data[i] = &tmp[i * (width + 2 * frame) * component];
        }
        return ImageSharedPtr(new (ptr) Image(height, width, frame, component, ptr_data),
                              [=](Image* img) {
                                    img->~Image();
                                    imageAlloc.deallocate(img);
                                });
    }
    return nullptr;
}
