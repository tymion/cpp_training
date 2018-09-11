#include <iostream>
#include "gtest/gtest.h"
#include "pixel_3x8.h"
#include "pixel_4x8.h"

class PixelTest : public ::testing::Test
{
    protected:
        virtual void SetUp() {
        }

        virtual void TearDown() {
        }
};

TEST(PixelTest, pixel3x8)
{
    uint8_t data[13] = "1234567890ab";
    pixel_3x8 **pix = new pixel_3x8*[4];
    pix[0] = (pixel_3x8*) &data[0];
    pix[1] = (pixel_3x8*) &data[3];
    pix[2] = (pixel_3x8*) &data[6];
    pix[3] = (pixel_3x8*) &data[9];

    EXPECT_EQ(pix[0]->_red, '1');
    EXPECT_EQ(pix[0]->_green, '2');
    EXPECT_EQ(pix[0]->_blue, '3');
    EXPECT_EQ(pix[1]->_red, '4');
    EXPECT_EQ(pix[1]->_green, '5');
    EXPECT_EQ(pix[1]->_blue, '6');
    EXPECT_EQ(pix[3]->_red, '0');
    EXPECT_EQ(pix[3]->_green, 'a');
    EXPECT_EQ(pix[3]->_blue, 'b');
    free(pix);
}

TEST(PixelTest, pixel4x8)
{
    uint8_t data[17] = "1234567890abcdef";
    pixel_4x8 **pix = new pixel_4x8*[4];
    pix[0] = (pixel_4x8*) &data[0];
    pix[1] = (pixel_4x8*) &data[4];
    pix[2] = (pixel_4x8*) &data[8];
    pix[3] = (pixel_4x8*) &data[12];

    EXPECT_EQ(pix[0]->_red, '1');
    EXPECT_EQ(pix[0]->_green, '2');
    EXPECT_EQ(pix[0]->_blue, '3');
    EXPECT_EQ(pix[0]->_alpha, '4');
    EXPECT_EQ(pix[1]->_red, '5');
    EXPECT_EQ(pix[1]->_green, '6');
    EXPECT_EQ(pix[1]->_blue, '7');
    EXPECT_EQ(pix[1]->_alpha, '8');
    EXPECT_EQ(pix[3]->_red, 'c');
    EXPECT_EQ(pix[3]->_green, 'd');
    EXPECT_EQ(pix[3]->_blue, 'e');
    EXPECT_EQ(pix[3]->_alpha, 'f');
    free(pix);
}
