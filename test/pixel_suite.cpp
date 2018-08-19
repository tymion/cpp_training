#include <iostream>
#include "gtest/gtest.h"
#include "pixel.h"
#include "pixel_3x8.h"

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
    uint8_t data[10] = "123456789";
    printf("%s\n", data);
    printf("%c\n", data[0]);

    printf("%d\n", sizeof(pixel_3x8));
//    pixel_3x8 **pix = new pixel_3x8*[4];
    pixel_3x8 *pix = (pixel_3x8*) data;
    //pix[1] = (pixel_3x8*) &data[3];
    //pix[2] = (pixel_3x8*) &data[6];
    //pix[3] = (pixel_3x8*) &data[9];

    EXPECT_EQ(pix->_red, '1');
    EXPECT_EQ(pix->_green, '2');
    EXPECT_EQ(pix->_blue, '3');
}
