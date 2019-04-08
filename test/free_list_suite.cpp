#include <iostream>
#include <cstdio>
#include "gtest/gtest.h"
#include "free_list.h"
#include "allocator.h"
#include "stack_allocator.h"

class FreeListTest : public ::testing::Test
{
    protected:
        FreeList<StackAllocator<uint32_t, 10, 512>, 512> allocator;
        uint32_t data[2048];

        virtual void SetUp() {
        }

        virtual void TearDown() {
        }
};

TEST_F(FreeListTest, allocate_success)
{
    Blk& mem = allocator.allocate(512);
    EXPECT_EQ(mem.ptr != nullptr, true);
}

TEST_F(FreeListTest, allocate_zero)
{
    Blk& mem = allocator.allocate(0);
    EXPECT_EQ(mem.ptr, nullptr);
}

TEST_F(FreeListTest, deallocate_null)
{
    Blk mem = { nullptr, 512 };
    allocator.deallocate(mem);
    EXPECT_EQ(mem.ptr, nullptr);
}

TEST_F(FreeListTest, allocate_and_deallocate)
{
    Blk& mem = allocator.allocate(512);
    allocator.deallocate(mem);
    EXPECT_EQ(mem.ptr, nullptr);
}
