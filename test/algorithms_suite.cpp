#include <iostream>
#include "gtest/gtest.h"
#include "algorithms.h"
#include "mask.h"
#include "pixel_3x8.h"
#include "pixel_4x8.h"

class AlgorithmsTest : public ::testing::Test
{
    protected:
        virtual void SetUp() {
        }

        virtual void TearDown() {
        }
};

#define ROW 5
#define COL 2

uint8_t data1_3x8_30[ROW*COL*3] = {
    0x1f, 0x1e, 0x1d, 0x0f, 0x0e, 0x0d,
    0x0c, 0x0b, 0x0a, 0x0c, 0x0b, 0x0a,
    0x09, 0x08, 0x07, 0x09, 0x08, 0x07,
    0x06, 0x05, 0x04, 0x06, 0x05, 0x04,
    0x03, 0x02, 0x01, 0x03, 0x02, 0x01,
};

uint8_t data1_4x8_30[20] = {
    0x01, 0x02, 0x03, 0x04,
    0x05, 0x06, 0x07, 0x08,
    0x09, 0x0a, 0x0b, 0x0c,
    0x0d, 0x0e, 0x0f, 0x10,
    0x11, 0x12, 0x13, 0x14
};

uint8_t data2_3x8_30[ROW*COL*3] = {
    0x0f, 0x0e, 0x0d, 0x0f, 0x0e, 0x0d,
    0x0c, 0x0b, 0x0a, 0x0c, 0x0b, 0x0a,
    0x09, 0x08, 0x07, 0x09, 0x08, 0x07,
    0x06, 0x05, 0x04, 0x06, 0x05, 0x04,
    0x03, 0x02, 0x01, 0x03, 0x02, 0x01,
};

uint8_t data2_4x8_30[20] = {
    0x44, 0x43, 0x42, 0x41,
    0x40, 0x4f, 0x4e, 0x4d,
    0x4c, 0x4b, 0x4a, 0x49,
    0x08, 0x07, 0x06, 0x05,
    0x04, 0x03, 0x02, 0x01,
};

uint8_t data3_3x8_30[ROW*COL*3] = {
    0x0f, 0x0e, 0x0d, 0x0f, 0x0e, 0x0d,
    0x0c, 0x0b, 0x0a, 0x0c, 0x0b, 0x0a,
    0x09, 0x08, 0x07, 0x09, 0x08, 0x07,
    0x06, 0x05, 0x04, 0x06, 0x05, 0x04,
    0x03, 0x02, 0x01, 0x03, 0x02, 0x01,
};

uint8_t data4_3x8_30[ROW*COL*3] = {
    0x1f, 0x1e, 0x0d, 0x0f, 0x0e, 0x0d,
    0x0c, 0x0b, 0x0a, 0x0c, 0x0b, 0x0a,
    0x09, 0x08, 0x07, 0x09, 0x08, 0x07,
    0x06, 0x05, 0x04, 0x06, 0x05, 0x04,
    0x03, 0x02, 0x01, 0x03, 0x02, 0x01,
};

TEST(AlgorithmsTest, index_jacarda_pixel3x8_same)
{
    Configuration::setSimilarityThreshold(10);
    Configuration::setJacardThreshold(0.9);
    pixel_3x8 **pixel1 = (pixel_3x8 **) malloc(ROW * sizeof(pixel_3x8 *));
    pixel_3x8 **pixel2 = (pixel_3x8 **) malloc(ROW * sizeof(pixel_3x8 *));
    for (int i = 0 ; i < ROW; i++) {
        pixel1[i] = (pixel_3x8 *) &data2_3x8_30[i*3*COL];
        pixel2[i] = (pixel_3x8 *) &data3_3x8_30[i*3*COL];
    }
    EXPECT_EQ(count_index_jacarda(pixel1, pixel2, ROW, COL), 1);
    free(pixel1);
    free(pixel2);
}

TEST(AlgorithmsTest, index_jacarda_pixel3x8_similar)
{
    Configuration::setSimilarityThreshold(10);
    Configuration::setJacardThreshold(0.9);
    pixel_3x8 **pixel1 = (pixel_3x8 **) malloc(ROW * sizeof(pixel_3x8 *));
    pixel_3x8 **pixel2 = (pixel_3x8 **) malloc(ROW * sizeof(pixel_3x8 *));
    for (int i = 0 ; i < ROW; i++) {
        pixel1[i] = (pixel_3x8 *) &data2_3x8_30[i*3*COL];
        pixel2[i] = (pixel_3x8 *) &data4_3x8_30[i*3*COL];
    }
    EXPECT_EQ(count_index_jacarda(pixel1, pixel2, ROW, COL), 0.9);
    free(pixel1);
    free(pixel2);
}

TEST(AlgorithmsTest, classic_compare_same)
{
    pixel_3x8 **pixel1 = (pixel_3x8 **) malloc(ROW * sizeof(pixel_3x8 *));
    pixel_3x8 **pixel2 = (pixel_3x8 **) malloc(ROW * sizeof(pixel_3x8 *));
    for (int i = 0 ; i < ROW; i++) {
        pixel1[i] = (pixel_3x8 *) &data2_3x8_30[i*3*COL];
        pixel2[i] = (pixel_3x8 *) &data3_3x8_30[i*3*COL];
    }
    EXPECT_TRUE(classic_compare(pixel1, pixel2, ROW, COL));
    free(pixel1);
    free(pixel2);
}

TEST(AlgorithmsTest, classic_compare_different)
{
    pixel_3x8 **pixel1 = (pixel_3x8 **) malloc(ROW * sizeof(pixel_3x8 *));
    pixel_3x8 **pixel2 = (pixel_3x8 **) malloc(ROW * sizeof(pixel_3x8 *));
    for (int i = 0 ; i < ROW; i++) {
        pixel1[i] = (pixel_3x8 *) &data2_3x8_30[i*3*COL];
        pixel2[i] = (pixel_3x8 *) &data4_3x8_30[i*3*COL];
    }
    EXPECT_FALSE(classic_compare(pixel1, pixel2, ROW, COL));
    free(pixel1);
    free(pixel2);
}
