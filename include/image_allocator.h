#pragma once

#include "image.h"
#include "mm/allocator.h"
#include "mm/stack_allocator.h"
#include "mm/fixed_size_free_list.h"
#include "mm/stack_free_list.h"
#include "logger.h"

constexpr size_t N = 10;

using Conf = Configuration;
constexpr uint32_t max_width = Conf::getImageWidth() + 2 * Conf::getImageFrame();

class ImageAllocator
{
    private:
        using StackImageSmall = StackImage<Conf::getImageHeight(),
                                            Conf::getImageWidth(),
                                            Conf::getImageFrame(), 1>;
        using StackImageBig = StackImage<Conf::getImageHeight(),
                                            Conf::getImageWidth(),
                                            Conf::getImageFrame(), 3>;

        FixedSizeFreeList<
            StackAllocator<sizeof(StackImageSmall), N>,
            sizeof(StackImageSmall)
                        > stackImageSmallAlloc;

        FixedSizeFreeList<
            StackAllocator<sizeof(StackImageBig), N>,
            sizeof(StackImageBig)
                        > stackImageBigAlloc;

        FixedSizeFreeList<
            StackAllocator<sizeof(Image), N>,
            sizeof(Image)
                        > imageAlloc;
        StackFreeList<4096> alloc;

    public:
        ImageSharedPtr allocate(uint32_t height, uint32_t width, uint8_t frame,
                                uint8_t component)
        {
            if (Conf::getImageHeight() == height && Conf::getImageFrame() == frame) {
                if (max_width * 3 == (width + 2 * frame) * component) {
                    return ImageSharedPtr(new (stackImageBigAlloc.allocate())
                                            StackImageBig(), [=](Image* img)
                            {
                                img->~Image();
                                stackImageBigAlloc.deallocate(img);
                            });
                } else if (max_width * 1 == (width + 2 * frame) * component) {
                    return ImageSharedPtr(new (stackImageSmallAlloc.allocate())
                                            StackImageSmall(), [=](Image* img)
                            {
                                img->~Image();
                                stackImageSmallAlloc.deallocate(img);
                            });
                }
            } else {
                uint8_t **ptr = static_cast<uint8_t**>(alloc.allocate(height + 2 * frame * sizeof(uint8_t*)).ptr);
                uint8_t *tmp = static_cast<uint8_t*>(alloc.allocate(
                                                        (height + 2 * frame) *
                                                        (width + 2 * frame) * component).ptr);
                for (uint8_t i = 0; i < height + 2 * frame; i++) {
                    ptr[i] = &tmp[i * (width + 2 * frame) * component];
                }
                return ImageSharedPtr(new (imageAlloc.allocate())
                                        Image(height, width, frame, component, ptr),
                                        [=](Image* img)
                            {
                                img->~Image();
                                imageAlloc.deallocate(img);
                            });
            }
            return nullptr;
        }
};
