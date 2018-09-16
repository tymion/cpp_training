#include <iostream>
#include "gtest/gtest.h"
#include "region.h"
#include "mask.h"
#include "pixel_3x8.h"
#include "pixel_4x8.h"

class RegionTest : public ::testing::Test
{
    protected:
        virtual void SetUp() {
        }

        virtual void TearDown() {
        }
};

TEST(RegionTest, Region_pixel3x8_allocate_and_delete)
{
    Region<pixel_3x8> *reg1 = new Region<pixel_3x8>(5,5);
    Region<pixel_3x8> *reg2 = new Region<pixel_3x8>(5,5);
    EXPECT_EQ(*reg1 == *reg2, true);
    delete reg1;
    delete reg2;
}

TEST(RegionTest, Region_pixel3x8_same)
{
    Region<pixel_3x8> *reg1 = new Region<pixel_3x8>(5,5);
    EXPECT_EQ(reg1->getHeight(), (uint32_t) 5);
    EXPECT_EQ(reg1->getWidth(), (uint32_t) 5);

    Region<pixel_3x8> *reg2 = new Region<pixel_3x8>(5,5);
    EXPECT_EQ(reg2->getHeight(), (uint32_t) 5);
    EXPECT_EQ(reg2->getWidth(), (uint32_t) 5);

    uint8_t data1[15] = {
        0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b,
        0x0c, 0x0d, 0x0e, 0x0f
    };
    uint8_t data2[15] = {
        0x0f, 0x0e, 0x0d, 0x0c, 0x0b, 0x0a, 0x09, 0x08, 0x07, 0x06, 0x05,
        0x04, 0x03, 0x02, 0x01,
    };
    uint8_t data_test[15] = {
        0x0f, 0x0e, 0x0d, 0x0c, 0x0b, 0x0a, 0x09, 0x08, 0x07, 0x06, 0x05,
        0x04, 0x03, 0x02, 0x01,
    };
    reg1->setData(0, data1);
    reg1->setData(1, data2);
    reg1->setData(2, (uint8_t*)"543212345432123");
    reg1->setData(3, (uint8_t*)"123454321234543");
    reg1->setData(4, (uint8_t*)"543212345432123");

    reg2->setData(0, data1);
    reg2->setData(1, data_test);
    reg2->setData(2, (uint8_t*)"543212345432123");
    reg2->setData(3, (uint8_t*)"123454321234543");
    reg2->setData(4, (uint8_t*)"543212345432123");

    EXPECT_EQ(*reg1 == *reg2, true);

    delete reg1;
    delete reg2;
}

TEST(RegionTest, Region_pixel3x8_different)
{
    Region<pixel_3x8> *reg1 = new Region<pixel_3x8>(5,5);
    EXPECT_EQ(reg1->getHeight(), (uint32_t) 5);
    EXPECT_EQ(reg1->getWidth(), (uint32_t) 5);

    Region<pixel_3x8> *reg2 = new Region<pixel_3x8>(5,5);
    EXPECT_EQ(reg2->getHeight(), (uint32_t) 5);
    EXPECT_EQ(reg2->getWidth(), (uint32_t) 5);

    reg1->setData(0, (uint8_t*)"543212345432123");
    reg1->setData(1, (uint8_t*)"123454321234543");
    reg1->setData(2, (uint8_t*)"543212345432123");
    reg1->setData(3, (uint8_t*)"123454321234543");
    reg1->setData(4, (uint8_t*)"543212345432123");

    reg2->setData(0, (uint8_t*)"=43212345432123");
    reg2->setData(1, (uint8_t*)"123454321234543");
    reg2->setData(2, (uint8_t*)"543212345432123");
    reg2->setData(3, (uint8_t*)"123454321234543");
    reg2->setData(4, (uint8_t*)"543212345432123");

    EXPECT_EQ(*reg1 == *reg2, false);

    delete reg1;
    delete reg2;
}

TEST(RegionBaseTest, Region_pixel3x8_same)
{
    RegionBase *reg1 = (RegionBase*) new Region<pixel_3x8>(5,5);
    EXPECT_EQ(reg1->getHeight(), (uint32_t) 5);
    EXPECT_EQ(reg1->getWidth(), (uint32_t) 5);

    RegionBase *reg2 = (RegionBase*) new Region<pixel_3x8>(5,5);
    EXPECT_EQ(reg2->getHeight(), (uint32_t) 5);
    EXPECT_EQ(reg2->getWidth(), (uint32_t) 5);

    reg1->setData(0, (uint8_t*)"543212345432123");
    reg1->setData(1, (uint8_t*)"123454321234543");
    reg1->setData(2, (uint8_t*)"543212345432123");
    reg1->setData(3, (uint8_t*)"123454321234543");
    reg1->setData(4, (uint8_t*)"543212345432123");

    reg2->setData(0, (uint8_t*)"543212345432123");
    reg2->setData(1, (uint8_t*)"123454321234543");
    reg2->setData(2, (uint8_t*)"543212345432123");
    reg2->setData(3, (uint8_t*)"123454321234543");
    reg2->setData(4, (uint8_t*)"543212345432123");

    EXPECT_EQ(*reg1 == *reg2, true);

    delete reg1;
    delete reg2;
}

TEST(RegionBaseTest, Region_pixel3x8_different)
{
    RegionBase *reg1 = (RegionBase*) new Region<pixel_3x8>(5,5);
    EXPECT_EQ(reg1->getHeight(), (uint32_t) 5);
    EXPECT_EQ(reg1->getWidth(), (uint32_t) 5);

    RegionBase *reg2 = (RegionBase*) new Region<pixel_3x8>(5,5);
    EXPECT_EQ(reg2->getHeight(), (uint32_t) 5);
    EXPECT_EQ(reg2->getWidth(), (uint32_t) 5);

    reg1->setData(0, (uint8_t*)"543212345432123");
    reg1->setData(1, (uint8_t*)"123454321234543");
    reg1->setData(2, (uint8_t*)"543212345432123");
    reg1->setData(3, (uint8_t*)"123454321234543");
    reg1->setData(4, (uint8_t*)"543212345432123");

    reg2->setData(0, (uint8_t*)"=43212345432123");
    reg2->setData(1, (uint8_t*)"123454321234543");
    reg2->setData(2, (uint8_t*)"543212345432123");
    reg2->setData(3, (uint8_t*)"123454321234543");
    reg2->setData(4, (uint8_t*)"543212345432123");

    EXPECT_EQ(*reg1 == *reg2, false);

    delete reg1;
    delete reg2;
}

TEST(RegionTest, Region_pixel4x8_same)
{
    Region<pixel_4x8> *reg1 = new Region<pixel_4x8>(5,5);
    EXPECT_EQ(reg1->getHeight(), (uint32_t) 5);
    EXPECT_EQ(reg1->getWidth(), (uint32_t) 5);

    Region<pixel_4x8> *reg2 = new Region<pixel_4x8>(5,5);
    EXPECT_EQ(reg2->getHeight(), (uint32_t) 5);
    EXPECT_EQ(reg2->getWidth(), (uint32_t) 5);

    reg1->setData(0, (uint8_t*)"54321234543212345432");
    reg1->setData(1, (uint8_t*)"12345432123454321234");
    reg1->setData(2, (uint8_t*)"54321234543212345432");
    reg1->setData(3, (uint8_t*)"12345432123454321234");
    reg1->setData(4, (uint8_t*)"54321234543212345432");

    reg2->setData(0, (uint8_t*)"54321234543212345432");
    reg2->setData(1, (uint8_t*)"12345432123454321234");
    reg2->setData(2, (uint8_t*)"54321234543212345432");
    reg2->setData(3, (uint8_t*)"12345432123454321234");
    reg2->setData(4, (uint8_t*)"54321234543212345432");

    EXPECT_EQ(*reg1 == *reg2, true);

    delete reg1;
    delete reg2;
}

TEST(RegionTest, Region_pixel4x8_different)
{
    Region<pixel_4x8> *reg1 = new Region<pixel_4x8>(5,5);
    EXPECT_EQ(reg1->getHeight(), (uint32_t) 5);
    EXPECT_EQ(reg1->getWidth(), (uint32_t) 5);

    Region<pixel_4x8> *reg2 = new Region<pixel_4x8>(5,5);
    EXPECT_EQ(reg2->getHeight(), (uint32_t) 5);
    EXPECT_EQ(reg2->getWidth(), (uint32_t) 5);

    reg1->setData(0, (uint8_t*)"54321234543212345432");
    reg1->setData(1, (uint8_t*)"12345432123454321234");
    reg1->setData(2, (uint8_t*)"54321234543212345432");
    reg1->setData(3, (uint8_t*)"12345432123454321234");
    reg1->setData(4, (uint8_t*)"54321234543212345432");

    reg2->setData(0, (uint8_t*)"=4321234543212345432");
    reg2->setData(1, (uint8_t*)"12345432123454321234");
    reg2->setData(2, (uint8_t*)"54321234543212345432");
    reg2->setData(3, (uint8_t*)"12345432123454321234");
    reg2->setData(4, (uint8_t*)"54321234543212345432");

    EXPECT_EQ(*reg1 == *reg2, false);

    delete reg1;
    delete reg2;
}

TEST(RegionBaseTest, Region_pixel4x8_same)
{
    RegionBase *reg1 = (RegionBase*) new Region<pixel_4x8>(5,5);
    EXPECT_EQ(reg1->getHeight(), (uint32_t) 5);
    EXPECT_EQ(reg1->getWidth(), (uint32_t) 5);

    RegionBase *reg2 = (RegionBase*) new Region<pixel_4x8>(5,5);
    EXPECT_EQ(reg2->getHeight(), (uint32_t) 5);
    EXPECT_EQ(reg2->getWidth(), (uint32_t) 5);

    reg1->setData(0, (uint8_t*)"54321234543212345432");
    reg1->setData(1, (uint8_t*)"12345432123454321234");
    reg1->setData(2, (uint8_t*)"54321234543212345432");
    reg1->setData(3, (uint8_t*)"12345432123454321234");
    reg1->setData(4, (uint8_t*)"54321234543212345432");

    reg2->setData(0, (uint8_t*)"54321234543212345432");
    reg2->setData(1, (uint8_t*)"12345432123454321234");
    reg2->setData(2, (uint8_t*)"54321234543212345432");
    reg2->setData(3, (uint8_t*)"12345432123454321234");
    reg2->setData(4, (uint8_t*)"54321234543212345432");

    EXPECT_EQ(*reg1 == *reg2, true);
    delete reg1;
    delete reg2;
}

TEST(RegionBaseTest, Region_pixel4x8_different)
{
    RegionBase *reg1 = (RegionBase*) new Region<pixel_4x8>(5,5);
    EXPECT_EQ(reg1->getHeight(), (uint32_t) 5);
    EXPECT_EQ(reg1->getWidth(), (uint32_t) 5);

    RegionBase *reg2 = (RegionBase*) new Region<pixel_4x8>(5,5);
    EXPECT_EQ(reg2->getHeight(), (uint32_t) 5);
    EXPECT_EQ(reg2->getWidth(), (uint32_t) 5);

    reg1->setData(0, (uint8_t*)"54321234543212345432");
    reg1->setData(1, (uint8_t*)"12345432123454321234");
    reg1->setData(2, (uint8_t*)"54321234543212345432");
    reg1->setData(3, (uint8_t*)"12345432123454321234");
    reg1->setData(4, (uint8_t*)"54321234543212345432");

    reg2->setData(0, (uint8_t*)"=4321234543212345432");
    reg2->setData(1, (uint8_t*)"12345432123454321234");
    reg2->setData(2, (uint8_t*)"54321234543212345432");
    reg2->setData(3, (uint8_t*)"12345432123454321234");
    reg2->setData(4, (uint8_t*)"54321234543212345432");

    EXPECT_EQ(*reg1 == *reg2, false);
    delete reg1;
    delete reg2;
}

/*
TEST(RegionTest, Region_pixel4x8)
{
    uint8_t data[26] = "1111111111111111111111111";
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
}
*/
