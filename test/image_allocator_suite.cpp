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
}
/*
TEST_F(ImageAllocatortTest, allocate_zero)
{
    Image* mem = allocator.allocate(0);
    EXPECT_EQ(mem, nullptr);
}

TEST_F(ImageAllocatortTest, deallocate_null)
{
    allocator.deallocate(nullptr);
}

TEST_F(ImageAllocatortTest, allocate_and_deallocate)
{
    Image* mem = allocator.allocate(blk_size);
    allocator.deallocate(mem);
}

TEST_F(ImageAllocatortTest, multi_allocate_and_deallocate_order)
{
    Image* mem1 = allocator.allocate(blk_size);
    Image* mem2 = allocator.allocate(blk_size);
    EXPECT_EQ(mem1 != nullptr, true);
    EXPECT_EQ(mem2 != nullptr, true);
    void *tmp = mem1;
    allocator.deallocate(mem1);
    allocator.deallocate(mem2);
    mem1 = allocator.allocate(blk_size);
    EXPECT_EQ(mem1, tmp);
}

TEST_F(ImageAllocatortTest, allocate_all)
{
    Image* mem[IMAGE_ALLOCATOR_POOL_SIZE];
    for (uint8_t i = 0; i < IMAGE_ALLOCATOR_POOL_SIZE; i++) {
        mem[i] = allocator.allocate(blk_size);
        EXPECT_EQ(mem[i] != nullptr, true);
    }
    Image* tmpmem = allocator.allocate(blk_size);
    EXPECT_EQ(tmpmem, nullptr);
    for (uint8_t i = 0; i < IMAGE_ALLOCATOR_POOL_SIZE; i++) {
        allocator.deallocate(mem[i]);
    }
    for (uint8_t i = 0; i < IMAGE_ALLOCATOR_POOL_SIZE; i++) {
        mem[i] = allocator.allocate(blk_size);
        EXPECT_EQ(mem[i] != nullptr, true);
    }
    tmpmem = allocator.allocate(blk_size);
    EXPECT_EQ(tmpmem, nullptr);
}
*/
