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
    FILE *file = fopen("test/test.png", "rb");
    if (file == NULL) {
        std::cout << "Can't open test.png file" << std::endl;
    }
    return file;
}

TEST(LibPNGTest, getData)
{
    PNGFileWrapper *file = new PNGFileWrapper(openTestFile());
    EXPECT_EQ(file->getWidth(), (uint32_t) 500);
    EXPECT_EQ(file->getHeight(), (uint32_t) 200);
    EXPECT_EQ(file->getComponentCnt(), (uint8_t) 3);
    uint32_t dataLen = file->getWidth() * file->getHeight() * file->getComponentCnt();
    uint8_t *data = (uint8_t*) malloc(dataLen);
    EXPECT_EQ(file->getData(data, dataLen), (uint32_t)dataLen);
    free(data);
    delete file;
}

TEST(LibPNGTest, getters)
{
    PNGFileWrapper *file = new PNGFileWrapper(openTestFile());
    EXPECT_EQ(file->getWidth(), (uint32_t) 500);
    EXPECT_EQ(file->getHeight(), (uint32_t) 200);
    EXPECT_EQ(file->getComponentCnt(), (uint8_t) 3);
    EXPECT_EQ(file->getComponentSize(), (uint8_t) 8);
    delete file;
}

TEST(LibPNGTest, allocate_and_free)
{
    PNGFileWrapper *file = new PNGFileWrapper(openTestFile());
    delete file;
}
