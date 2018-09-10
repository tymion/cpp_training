#include <iostream>
#include "gtest/gtest.h"
#include "mask.h"

class MaskTest : public ::testing::Test
{
    protected:
        virtual void SetUp() {
        }

        virtual void TearDown() {
        }
};

TEST(MaskTest, success)
{
    uint8_t data[26] = "1111111111111111111111111";
    Mask *mask = new Mask(5, 5, data);

    EXPECT_EQ(mask->getMask(0, 0), '1');
    EXPECT_EQ(mask->getMask(0, 1), '1');
    EXPECT_EQ(mask->getMask(0, 2), '1');
    EXPECT_EQ(mask->getMask(0, 3), '1');
    EXPECT_EQ(mask->getMask(0, 4), '1');
    EXPECT_EQ(mask->getMask(1, 0), '1');
    EXPECT_EQ(mask->getMask(1, 1), '1');
    EXPECT_EQ(mask->getMask(1, 2), '1');
    EXPECT_EQ(mask->getMask(1, 3), '1');
    EXPECT_EQ(mask->getMask(1, 4), '1');
    EXPECT_EQ(mask->getMask(2, 0), '1');
    EXPECT_EQ(mask->getMask(2, 1), '1');
    EXPECT_EQ(mask->getMask(2, 2), '1');
    EXPECT_EQ(mask->getMask(2, 3), '1');
    EXPECT_EQ(mask->getMask(2, 4), '1');
    EXPECT_EQ(mask->getMask(3, 0), '1');
    EXPECT_EQ(mask->getMask(3, 1), '1');
    EXPECT_EQ(mask->getMask(3, 2), '1');
    EXPECT_EQ(mask->getMask(3, 3), '1');
    EXPECT_EQ(mask->getMask(3, 4), '1');
    EXPECT_EQ(mask->getMask(4, 0), '1');
    EXPECT_EQ(mask->getMask(4, 1), '1');
    EXPECT_EQ(mask->getMask(4, 2), '1');
    EXPECT_EQ(mask->getMask(4, 3), '1');
    EXPECT_EQ(mask->getMask(4, 4), '1');
    delete mask;
}

TEST(MaskTest, allocate_and_free)
{
    uint8_t data[26] = "1111111111111111111111111";
    Mask *mask = new Mask(5, 5, data);
    delete mask;
}
