#include <iostream>
#include <cstdio>
#include "gtest/gtest.h"
#include "libpng_wrapper.h"

class LibPNGTest : public ::testing::Test
{
    protected:
        virtual void SetUp() {
        }

        virtual void TearDown() {
        }
};

static FILE* openTestFile()
{
    FILE *file = fopen("test/test1.png", "rb");
    if (file == NULL) {
        std::cout << "Can't open test.png file" << std::endl;
    }
    return file;
}
/*
TEST(LibPNGTest, getData)
{
    PNGFileWrapper *file = new PNGFileWrapper(openTestFile());
    EXPECT_EQ(file->getWidth(), (uint32_t) 500);
    EXPECT_EQ(file->getHeight(), (uint32_t) 200);
    EXPECT_EQ(file->getComponentCnt(), (uint8_t) 4);
    uint8_t *data = NULL;
    EXPECT_EQ(file->getData(0, &data), true);
    delete file;
}
*/
TEST(LibPNGTest, getters)
{
    PNGFileWrapper *file = new PNGFileWrapper(openTestFile());
    EXPECT_EQ(file->getWidth(), (uint32_t) 500);
    EXPECT_EQ(file->getHeight(), (uint32_t) 200);
    EXPECT_EQ(file->getComponentSize(), (uint8_t) 8);
    EXPECT_EQ(file->getComponentCnt(), (uint8_t) 4);
    delete file;
}

TEST(LibPNGTest, allocate_and_free)
{
    PNGFileWrapper *file = new PNGFileWrapper(openTestFile());
    delete file;
}
