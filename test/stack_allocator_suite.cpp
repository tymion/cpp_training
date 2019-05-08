#include <iostream>
#include <cstdio>
#include "gtest/gtest.h"
#include "free_list.h"
#include "allocator.h"
#include "stack_allocator.h"

class StackAllocatorTest : public ::testing::Test
{
    protected:
        uint32_t blk_size = 512;
        uint8_t blk_cnt = 10;

        StackAllocator<10, 512> allocator;

        virtual void SetUp() {
        }

        virtual void TearDown() {
        }
};

TEST_F(StackAllocatorTest, allocate_success)
{
    Blk mem = allocator.allocate(blk_size);
    EXPECT_EQ(mem.ptr != nullptr, true);
}

TEST_F(StackAllocatorTest, allocate_edge_blk_size)
{
    Blk mem = allocator.allocate(blk_size + 1);
    EXPECT_EQ(mem.ptr, nullptr);
    allocator.deallocate(mem);
    mem = allocator.allocate(blk_size - 1);
    EXPECT_EQ(mem.ptr, nullptr);
}

TEST_F(StackAllocatorTest, allocate_zero)
{
    Blk mem = allocator.allocate(0);
    EXPECT_EQ(mem.ptr, nullptr);
}

TEST_F(StackAllocatorTest, deallocate_null)
{
    Blk mem = { nullptr, blk_size };
    allocator.deallocate(mem);
    EXPECT_EQ(mem.ptr, nullptr);
}

TEST_F(StackAllocatorTest, allocate_and_deallocate)
{
    Blk mem = allocator.allocate(blk_size);
    allocator.deallocate(mem);
    EXPECT_EQ(mem.ptr, nullptr);
}

TEST_F(StackAllocatorTest, allocate_and_owns_and_deallocate)
{
    Blk mem = allocator.allocate(blk_size);
    EXPECT_EQ(allocator.owns(mem), true);
    allocator.deallocate(mem);
}

TEST_F(StackAllocatorTest, owns_null)
{
    Blk mem = { nullptr, blk_size };
    EXPECT_EQ(allocator.owns(mem), false);
}

TEST_F(StackAllocatorTest, owns_invalid_pointer)
{
    Blk mem = { reinterpret_cast<void*>(0x100), blk_size };
    EXPECT_EQ(allocator.owns(mem), false);
}

TEST_F(StackAllocatorTest, allocate_and_owns_invalid_blk_size_and_deallocate)
{
    Blk mem = allocator.allocate(blk_size);
    mem.size = blk_size - 1;
    EXPECT_EQ(allocator.owns(mem), false);
    mem.size = blk_size + 1;
    EXPECT_EQ(allocator.owns(mem), false);
    allocator.deallocate(mem);
}

TEST_F(StackAllocatorTest, multi_allocate_and_deallocate_order)
{
    Blk mem1 = allocator.allocate(blk_size);
    Blk mem2 = allocator.allocate(blk_size);
    EXPECT_EQ(mem1.ptr != nullptr, true);
    EXPECT_EQ(mem2.ptr != nullptr, true);
    allocator.deallocate(mem1);
    EXPECT_EQ(mem1.ptr != nullptr, true);
    allocator.deallocate(mem2);
    EXPECT_EQ(mem2.ptr, nullptr);
    allocator.deallocate(mem1);
    EXPECT_EQ(mem1.ptr, nullptr);
}

TEST_F(StackAllocatorTest, allocate_all)
{
    Blk mem;
    for (uint8_t i = 0; i < blk_cnt; i++) {
        mem = allocator.allocate(blk_size);
        EXPECT_EQ(mem.ptr != nullptr, true);
    }
    mem = allocator.allocate(blk_size);
    EXPECT_EQ(mem.ptr, nullptr);
}
