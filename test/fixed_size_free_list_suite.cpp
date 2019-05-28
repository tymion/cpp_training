#include <iostream>
#include <cstdio>
#include "gtest/gtest.h"
#include "mm/fixed_size_free_list.h"
#include "mm/stack_allocator.h"

#define blk_cnt 10

typedef FixedSizeFreeList<StackAllocator<10, 512>, 512> FreeListAllocator;

class FixedSizeFreeListTest : public ::testing::Test
{
    protected:
        uint32_t blk_size = 512;

        FreeListAllocator allocator;

        virtual void SetUp() {
        }

        virtual void TearDown() {
        }
};

static void
free_mem_from_stack_to_free_list(FreeListAllocator *allocator, size_t blk_size)
{
    Blk mem1 = allocator->allocate(blk_size);
    allocator->allocate(blk_size);
    allocator->deallocate(mem1);
}

TEST_F(FixedSizeFreeListTest, allocate_success)
{
    free_mem_from_stack_to_free_list(&allocator, blk_size);

    Blk mem = allocator.allocate(blk_size);
    EXPECT_EQ(mem.ptr != nullptr, true);
}

TEST_F(FixedSizeFreeListTest, allocate_edge_blk_size)
{
    free_mem_from_stack_to_free_list(&allocator, blk_size);

    Blk mem = allocator.allocate(blk_size + 1);
    EXPECT_EQ(mem.ptr, nullptr);
    allocator.deallocate(mem);
    mem = allocator.allocate(blk_size - 1);
    EXPECT_EQ(mem.ptr, nullptr);
}

TEST_F(FixedSizeFreeListTest, allocate_zero)
{
    free_mem_from_stack_to_free_list(&allocator, blk_size);

    Blk mem = allocator.allocate(0);
    EXPECT_EQ(mem.ptr, nullptr);
}

TEST_F(FixedSizeFreeListTest, deallocate_null)
{
    free_mem_from_stack_to_free_list(&allocator, blk_size);

    Blk mem = { nullptr, blk_size };
    allocator.deallocate(mem);
    EXPECT_EQ(mem.ptr, nullptr);
}

TEST_F(FixedSizeFreeListTest, allocate_and_deallocate)
{
    free_mem_from_stack_to_free_list(&allocator, blk_size);

    Blk mem = allocator.allocate(blk_size);
    allocator.deallocate(mem);
    EXPECT_EQ(mem.ptr, nullptr);
}

TEST_F(FixedSizeFreeListTest, allocate_and_owns_and_deallocate)
{
    free_mem_from_stack_to_free_list(&allocator, blk_size);

    Blk mem = allocator.allocate(blk_size);
    EXPECT_EQ(allocator.owns(mem), true);
    allocator.deallocate(mem);
}

TEST_F(FixedSizeFreeListTest, owns_null)
{
    free_mem_from_stack_to_free_list(&allocator, blk_size);

    Blk mem = { nullptr, blk_size };
    EXPECT_EQ(allocator.owns(mem), false);
}

TEST_F(FixedSizeFreeListTest, owns_invalid_pointer)
{
    free_mem_from_stack_to_free_list(&allocator, blk_size);

    Blk mem = { reinterpret_cast<void*>(0x100), blk_size };
    EXPECT_EQ(allocator.owns(mem), false);
}

TEST_F(FixedSizeFreeListTest, allocate_and_owns_invalid_blk_size_and_deallocate)
{
    free_mem_from_stack_to_free_list(&allocator, blk_size);

    Blk mem = allocator.allocate(blk_size);
    mem.size = blk_size - 1;
    EXPECT_EQ(allocator.owns(mem), false);
    mem.size = blk_size + 1;
    EXPECT_EQ(allocator.owns(mem), false);
    allocator.deallocate(mem);
}

TEST_F(FixedSizeFreeListTest, multi_allocate_and_deallocate_order)
{
    Blk mem1 = allocator.allocate(blk_size);
    Blk mem2 = allocator.allocate(blk_size);
    EXPECT_EQ(mem1.ptr != nullptr, true);
    EXPECT_EQ(mem2.ptr != nullptr, true);
    void *tmp = mem1.ptr;
    allocator.deallocate(mem1);
    EXPECT_EQ(mem1.ptr, nullptr);
    allocator.deallocate(mem2);
    EXPECT_EQ(mem2.ptr, nullptr);
    mem1 = allocator.allocate(blk_size);
    EXPECT_EQ(mem1.ptr, tmp);
}

TEST_F(FixedSizeFreeListTest, allocate_all)
{
    Blk mem[blk_cnt];
    for (uint8_t i = 0; i < blk_cnt; i++) {
        mem[i] = allocator.allocate(blk_size);
        EXPECT_EQ(mem[i].ptr != nullptr, true);
    }
    Blk tmpmem = allocator.allocate(blk_size);
    EXPECT_EQ(tmpmem.ptr, nullptr);
    for (uint8_t i = 0; i < blk_cnt; i++) {
        allocator.deallocate(mem[i]);
        EXPECT_EQ(mem[i].ptr, nullptr);
    }
    for (uint8_t i = 0; i < blk_cnt; i++) {
        mem[i] = allocator.allocate(blk_size);
        EXPECT_EQ(mem[i].ptr != nullptr, true);
    }
    tmpmem = allocator.allocate(blk_size);
    EXPECT_EQ(tmpmem.ptr, nullptr);
}
