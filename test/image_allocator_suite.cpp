#include <iostream>
#include <cstdio>
#include "gtest/gtest.h"
#include "image_factory.h"

class ImageAllocatortTest : public ::testing::Test
{
    protected:
        uint32_t blk_size = 1024;
        ImageAllocator allocator;

        virtual void SetUp() {
        }

        virtual void TearDown() {
        }
};

TEST_F(ImageAllocatortTest, allocate_success)
{
    Image* mem = allocator.allocate(blk_size);
    EXPECT_EQ(mem != nullptr, true);
    allocator.deallocate(mem);
}
