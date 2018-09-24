#include <iostream>
#include "gtest/gtest.h"
#include "region_factory.h"
#include "iimage_mock.h"
#include "iimage.h"
#include "pixel_3x8.h"
#include "libpng_wrapper.h"

using namespace std;

class RegionFactoryTest : public ::testing::Test
{
    protected:
        virtual void SetUp() {
        }

        virtual void TearDown() {
        }
};

static FILE* openTestFile()
{
    FILE *file = fopen("test/test.png", "rb");
    if (file == NULL) {
        std::cout << "Can't open test.png file" << std::endl;
    }
    return file;
}

TEST(RegionFactoryTest, allocate_and_free_iimage_mock)
{
    IImage *iimage = (IImage*) new IImageMock_3x8();
    RegionFactory *fb = new RegionFactory(iimage);
    delete fb;
    delete iimage;
}

TEST(RegionFactoryTest, createRegion_iimage_mock)
{
    IImage *iimage = (IImage*) new IImageMock_3x8();
    RegionFactory *fb = new RegionFactory(iimage);
    RegionBase * reg = fb->createRegion(2,2);
    delete reg;
    delete fb;
    delete iimage;
}

TEST(RegionFactoryTest, updateRegion_iimage_mock)
{
    IImage *iimage = (IImage*) new IImageMock_3x8();
    RegionFactory *fb = new RegionFactory(iimage);
    RegionBase * reg1 = fb->createRegion(2,2);
    RegionBase *reg2 = (RegionBase*)new Region<pixel_3x8>(2, 2);
    uint8_t data_1[12] = {
        0x00, 0x01, 0x02, 0x03, 0x04, 0x05,
        0x12, 0x13, 0x14, 0x15, 0x16, 0x17
    };
    reg2->setData(0, data_1);
    reg2->setData(1, &data_1[6]);
    EXPECT_EQ(fb->updateRegion(0, 0, reg1), true);
    EXPECT_EQ(*reg1 == *reg2, true);
    uint8_t data_2[12] = {
        0x27, 0x28, 0x29, 0x2a, 0x2b, 0x2c,
        0x39, 0x3a, 0x3b, 0x3c, 0x3d, 0x3e
    };
    reg2->setData(0, data_2);
    reg2->setData(1, &data_2[6]);
    EXPECT_EQ(fb->updateRegion(2, 1, reg1), true);
    EXPECT_EQ(*reg1 == *reg2, true);
    delete reg1;
    delete reg2;
    delete fb;
    delete iimage;
}

TEST(RegionFactoryTest, allocate_and_free_libpng)
{
    IImage *iimage = (IImage*) new PNGFileWrapper(openTestFile());
    RegionFactory *fb = new RegionFactory(iimage);
    delete fb;
    delete iimage;
}

TEST(RegionFactoryTest, createRegion_libpng)
{
    IImage *iimage = (IImage*) new PNGFileWrapper(openTestFile());
    RegionFactory *fb = new RegionFactory(iimage);
    RegionBase * reg = fb->createRegion(2,2);
    delete reg;
    delete fb;
    delete iimage;
}
/*
TEST(RegionFactoryTest, updateRegion_libpng)
{
    IImage *iimage = (IImage*) new PNGFileWrapper(openTestFile());
    RegionFactory *fb = new RegionFactory(iimage);
    RegionBase * reg1 = fb->createRegion(2,2);
    RegionBase *reg2 = (RegionBase*)new Region<pixel_3x8>(2, 2);
    uint8_t data_1[12] = {
        0x00, 0x01, 0x02, 0x03, 0x04, 0x05,
        0x12, 0x13, 0x14, 0x15, 0x16, 0x17
    };
    reg2->setData(0, data_1);
    reg2->setData(1, &data_1[6]);
    EXPECT_EQ(fb->updateRegion(0, 0, reg1), true);
    EXPECT_EQ(*reg1 == *reg2, true);
    uint8_t data_2[12] = {
        0x27, 0x28, 0x29, 0x2a, 0x2b, 0x2c,
        0x39, 0x3a, 0x3b, 0x3c, 0x3d, 0x3e
    };
    reg2->setData(0, data_2);
    reg2->setData(1, &data_2[6]);
    EXPECT_EQ(fb->updateRegion(2, 1, reg1), true);
    EXPECT_EQ(*reg1 == *reg2, true);
    delete reg1;
    delete reg2;
    delete fb;
    delete iimage;
}
*/
