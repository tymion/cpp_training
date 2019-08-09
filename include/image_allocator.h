#pragma once

#include "image.h"
#include "mm/allocator.h"
#include "mm/stack_allocator.h"
#include "mm/fixed_size_free_list.h"
#include "mm/stack_free_list.h"
#include "config.h"
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
        ImageAllocator() {
            LOG("==============================================================\n");
        }

        ImageSharedPtr allocate(uint32_t height, uint32_t width, uint8_t frame,
                                uint8_t component);
};
