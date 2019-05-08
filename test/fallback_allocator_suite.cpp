#include <iostream>
#include <cstdio>
#include "gtest/gtest.h"
#include "allocator.h"
#include "fallback_allocator.h"
#include "nullptr_allocator.h"
#include "mallocator.h"
#include "stack_allocator.h"
#include "free_list.h"
#include "image_factory.h"

class FallbackAllocatorTest : public ::testing::Test
{
    protected:

        FallbackAllocator<
            NullPtrAllocator,
            Mallocator> allocator1;

        FallbackAllocator<
            Mallocator,
            NullPtrAllocator> allocator2;

        FallbackAllocator<
            FreeList<
                StackAllocator<IMAGE_ALLOCATOR_POOL_SIZE, sizeof(Image)>,
                sizeof(Image)>,
            Mallocator> allocator3;

        uint32_t blk_size = sizeof(Image);
        uint32_t blk_cnt = IMAGE_ALLOCATOR_POOL_SIZE;

        virtual void SetUp() {
        }

        virtual void TearDown() {
        }
};

TEST_F(FallbackAllocatorTest, allocate_success)
{
    Blk mem = allocator1.allocate(blk_size);
    EXPECT_EQ(mem.ptr != nullptr, true);
    allocator1.deallocate(mem);
    EXPECT_EQ(mem.ptr, nullptr);
    EXPECT_EQ(mem.size, 0);

    mem = allocator2.allocate(blk_size);
    EXPECT_EQ(mem.ptr != nullptr, true);
    allocator2.deallocate(mem);
    EXPECT_EQ(mem.ptr, nullptr);
    EXPECT_EQ(mem.size, 0);

    mem = allocator3.allocate(blk_size);
    EXPECT_EQ(mem.ptr != nullptr, true);
    allocator3.deallocate(mem);
    EXPECT_EQ(mem.ptr, nullptr);
    EXPECT_EQ(mem.size, 0);
}

TEST_F(FallbackAllocatorTest, allocate_zero)
{
    Blk mem = allocator1.allocate(0);
    EXPECT_EQ(mem.ptr != nullptr, true);
    allocator1.deallocate(mem);
    EXPECT_EQ(mem.ptr, nullptr);
    EXPECT_EQ(mem.size, 0);

    mem = allocator2.allocate(0);
    EXPECT_EQ(mem.ptr != nullptr, true);
    allocator2.deallocate(mem);
    EXPECT_EQ(mem.ptr, nullptr);
    EXPECT_EQ(mem.size, 0);

    mem = allocator3.allocate(0);
    EXPECT_EQ(mem.ptr != nullptr, true);
    allocator3.deallocate(mem);
    EXPECT_EQ(mem.ptr, nullptr);
    EXPECT_EQ(mem.size, 0);
}

TEST_F(FallbackAllocatorTest, deallocate_null)
{
    Blk mem = { nullptr, blk_size };
    allocator1.deallocate(mem);
    EXPECT_EQ(mem.ptr, nullptr);

    mem = { nullptr, blk_size };
    allocator2.deallocate(mem);
    EXPECT_EQ(mem.ptr, nullptr);

    mem = { nullptr, blk_size };
    allocator3.deallocate(mem);
    EXPECT_EQ(mem.ptr, nullptr);
}

TEST_F(FallbackAllocatorTest, allocate_and_deallocate)
{
    Blk mem = allocator1.allocate(blk_size);
    EXPECT_EQ(mem.ptr != nullptr, true);
    allocator1.deallocate(mem);
    EXPECT_EQ(mem.ptr, nullptr);

    mem = allocator2.allocate(blk_size);
    EXPECT_EQ(mem.ptr != nullptr, true);
    allocator2.deallocate(mem);
    EXPECT_EQ(mem.ptr, nullptr);

    mem = allocator3.allocate(blk_size);
    EXPECT_EQ(mem.ptr != nullptr, true);
    allocator3.deallocate(mem);
    EXPECT_EQ(mem.ptr, nullptr);
}

TEST_F(FallbackAllocatorTest, allocate_and_owns_and_deallocate)
{
    Blk mem = allocator1.allocate(blk_size);
    EXPECT_EQ(allocator1.owns(mem), true);
    allocator1.deallocate(mem);

    mem = allocator2.allocate(blk_size);
    EXPECT_EQ(allocator2.owns(mem), true);
    allocator2.deallocate(mem);

    mem = allocator3.allocate(blk_size);
    EXPECT_EQ(allocator3.owns(mem), true);
    allocator3.deallocate(mem);
}

TEST_F(FallbackAllocatorTest, owns_null)
{
    Blk mem = { nullptr, blk_size };
    EXPECT_EQ(allocator1.owns(mem), true);

    mem = { nullptr, blk_size };
    EXPECT_EQ(allocator2.owns(mem), true);

    mem = { nullptr, blk_size };
    EXPECT_EQ(allocator3.owns(mem), true);
}

TEST_F(FallbackAllocatorTest, owns_invalid_pointer)
{
    Blk mem = { reinterpret_cast<void*>(0x100), blk_size };
    EXPECT_EQ(allocator1.owns(mem), true);

    EXPECT_EQ(allocator2.owns(mem), true);

    EXPECT_EQ(allocator3.owns(mem), true);
}

TEST_F(FallbackAllocatorTest, allocate_and_owns_invalid_blk_size_and_deallocate)
{
    Blk mem = allocator3.allocate(blk_size);
    mem.size = blk_size - 1;
    EXPECT_EQ(allocator3.owns(mem), true);
    mem.size = blk_size + 1;
    EXPECT_EQ(allocator3.owns(mem), true);
    mem.size = blk_size;
    allocator3.deallocate(mem);
}

TEST_F(FallbackAllocatorTest, multi_allocate_and_deallocate_order)
{
    Blk mem1 = allocator3.allocate(blk_size);
    Blk mem2 = allocator3.allocate(blk_size);
    EXPECT_EQ(mem1.ptr != nullptr, true);
    EXPECT_EQ(mem2.ptr != nullptr, true);
    void *tmp = mem1.ptr;
    allocator3.deallocate(mem1);
    EXPECT_EQ(mem1.ptr, nullptr);
    allocator3.deallocate(mem2);
    EXPECT_EQ(mem2.ptr, nullptr);
    mem1 = allocator3.allocate(blk_size);
    EXPECT_EQ(mem1.ptr, tmp);
}

TEST_F(FallbackAllocatorTest, allocate_all)
{
    Blk mem[blk_cnt];
    for (uint8_t i = 0; i < blk_cnt; i++) {
        mem[i] = allocator3.allocate(blk_size);
        EXPECT_EQ(mem[i].ptr != nullptr, true);
    }
    Blk tmpmem = allocator3.allocate(blk_size);
    EXPECT_EQ(tmpmem.ptr != nullptr, true);
    allocator3.deallocate(tmpmem);
    EXPECT_EQ(tmpmem.ptr, nullptr);
    EXPECT_EQ(tmpmem.size, 0);
    for (uint8_t i = 0; i < blk_cnt; i++) {
        allocator3.deallocate(mem[i]);
        EXPECT_EQ(mem[i].ptr, nullptr);
    }
    for (uint8_t i = 0; i < blk_cnt; i++) {
        mem[i] = allocator3.allocate(blk_size);
        EXPECT_EQ(mem[i].ptr != nullptr, true);
    }
    tmpmem = allocator3.allocate(blk_size);
    EXPECT_EQ(tmpmem.ptr != nullptr, true);
    allocator3.deallocate(tmpmem);
}
