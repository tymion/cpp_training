#include <iostream>
#include <cstdio>
#include "gtest/gtest.h"
#include "allocator.h"
#include "nullptr_allocator.h"

class NullPtrAllocatorTest : public ::testing::Test
{
    protected:
        NullPtrAllocator allocator;

        virtual void SetUp() {
        }

        virtual void TearDown() {
        }
};

TEST_F(NullPtrAllocatorTest, allocate)
{
    Blk mem = allocator.allocate(0);
    EXPECT_EQ(mem.ptr, nullptr);
    EXPECT_EQ(mem.size, 0);
    mem = allocator.allocate(-1);
    EXPECT_EQ(mem.ptr, nullptr);
    EXPECT_EQ(mem.size, 0);
    mem = allocator.allocate(1);
    EXPECT_EQ(mem.ptr, nullptr);
    EXPECT_EQ(mem.size, 0);
}

TEST_F(NullPtrAllocatorTest, deallocate_null)
{
    Blk mem = { nullptr, 128 };
    allocator.deallocate(mem);
    EXPECT_EQ(mem.ptr, nullptr);
    EXPECT_EQ(mem.size, 0);
}

TEST_F(NullPtrAllocatorTest, deallocate_pointer)
{
    Blk mem = { reinterpret_cast<void*>(0x100), 32 };
    allocator.deallocate(mem);
    EXPECT_EQ(mem.ptr, reinterpret_cast<void*>(0x100));
    EXPECT_EQ(mem.size, 32);
}

TEST_F(NullPtrAllocatorTest, allocate_and_deallocate)
{
    Blk mem = allocator.allocate(16);
    allocator.deallocate(mem);
    EXPECT_EQ(mem.ptr, nullptr);
    EXPECT_EQ(mem.size, 0);
}

TEST_F(NullPtrAllocatorTest, allocate_and_owns_and_deallocate)
{
    Blk mem = allocator.allocate(5);
    EXPECT_EQ(allocator.owns(mem), true);
    allocator.deallocate(mem);
    EXPECT_EQ(mem.ptr, nullptr);
    EXPECT_EQ(mem.size, 0);
}

TEST_F(NullPtrAllocatorTest, owns_null_and_large_size)
{
    Blk mem = { nullptr, 1024 };
    EXPECT_EQ(allocator.owns(mem), false);
}

TEST_F(NullPtrAllocatorTest, owns_pointer)
{
    Blk mem = { reinterpret_cast<void*>(0x100), 0 };
    EXPECT_EQ(allocator.owns(mem), false);
}
