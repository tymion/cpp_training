#include <iostream>
#include <cstdio>
#include "gtest/gtest.h"
#include "libpng_wrapper.h"
#include "region.h"
#include "region_factory.h"

class IntegrationTest : public ::testing::Test
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

static FILE* openTestFile2()
{
    FILE *file = fopen("test/test2.png", "rb");
    if (file == NULL) {
        std::cout << "Can't open test.png file" << std::endl;
    }
    return file;
}

TEST(IntegrationTest, getData)
{
    std::shared_ptr<IImage> lImage = std::shared_ptr<IImage>((IImage *) new PNGFileWrapper(openTestFile()));
    std::shared_ptr<IImage> rImage = std::shared_ptr<IImage>((IImage *) new PNGFileWrapper(openTestFile2()));
    uint32_t size = 7;
    uint32_t height = lImage->getHeight();
    uint32_t width = lImage->getWidth();
    std::unique_ptr<RegionFactory> lbuffer = std::unique_ptr<RegionFactory>(new RegionFactory(lImage));
    std::unique_ptr<RegionFactory> rbuffer = std::unique_ptr<RegionFactory>(new RegionFactory(rImage));
    RegionBase *rregion = rbuffer->createRegion(size, size);
    RegionBase *lregion = lbuffer->createRegion(size, size);
    uint32_t cnt = 0;
    uint32_t cnt2 = 0;
    for (uint32_t row = 0; row < height - size; row++) {
        for (uint32_t col = 0; col < width - size; col++) {
            rbuffer->updateRegion(row, col, rregion);
            lbuffer->updateRegion(row, col, lregion);
            if (*rregion == *lregion) {
                cnt++;
            }
            cnt2++;
        }
    }

    std::cout << "Cnt:" << cnt << " Cnt2:" << cnt2 << std::endl;
    EXPECT_EQ(cnt, cnt2);
    delete rregion;
    delete lregion;
}
