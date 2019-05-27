#include <iostream>
#include <cstdio>
#include "gtest/gtest.h"
#include "mm/allocator.h"
#include "mm/mallocator.h"

class MallocatorTest : public ::testing::Test
{
    protected:
        Mallocator allocator;

        virtual void SetUp() {
        }

        virtual void TearDown() {
        }
};

TEST_F(MallocatorTest, allocate)
{
    Blk mem = allocator.allocate(0);
    EXPECT_EQ(mem.ptr != nullptr, true);
    allocator.deallocate(mem);
    EXPECT_EQ(mem.size, 0);
    allocator.deallocate(mem);
    EXPECT_EQ(mem.ptr, nullptr);
    EXPECT_EQ(mem.size, 0);
    mem = allocator.allocate(1);
    EXPECT_EQ(mem.ptr != nullptr, true);
    EXPECT_EQ(mem.size, 1);
    allocator.deallocate(mem);
    EXPECT_EQ(mem.ptr, nullptr);
    EXPECT_EQ(mem.size, 0);
}

TEST_F(MallocatorTest, deallocate_null)
{
    Blk mem = { nullptr, 128 };
    allocator.deallocate(mem);
    EXPECT_EQ(mem.ptr, nullptr);
    EXPECT_EQ(mem.size, 0);
}

TEST_F(MallocatorTest, allocate_and_deallocate)
{
    Blk mem = allocator.allocate(16);
    allocator.deallocate(mem);
    EXPECT_EQ(mem.ptr, nullptr);
    EXPECT_EQ(mem.size, 0);
}

TEST_F(MallocatorTest, allocate_and_owns_and_deallocate)
{
    Blk mem = allocator.allocate(5);
    EXPECT_EQ(allocator.owns(mem), true);
    allocator.deallocate(mem);
    EXPECT_EQ(mem.ptr, nullptr);
    EXPECT_EQ(mem.size, 0);
}

TEST_F(MallocatorTest, owns_null_and_large_size)
{
    Blk mem = { nullptr, 1024 };
    EXPECT_EQ(allocator.owns(mem), true);
    mem = { nullptr, 0 };
    EXPECT_EQ(allocator.owns(mem), false);
}
