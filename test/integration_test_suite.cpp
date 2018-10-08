#include <iostream>
#include <cstdio>
#include "gtest/gtest.h"
#include "libpng_wrapper.h"
#include "region.h"
#include "region_factory.h"

using namespace std;

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
        cout << "Can't open test.png file" << endl;
    }
    return file;
}

static FILE* openTestFile2()
{
    FILE *file = fopen("test/test2.png", "rb");
    if (file == NULL) {
        cout << "Can't open test.png file" << endl;
    }
    return file;
}

TEST(IntegrationTest, getData)
{
    shared_ptr<IImage> lImage((IImage *) new PNGFileWrapper(openTestFile()));
    shared_ptr<IImage> rImage((IImage *) new PNGFileWrapper(openTestFile2()));
    uint32_t size = 7;
    uint32_t height = lImage->getHeight();
    uint32_t width = lImage->getWidth();
    unique_ptr<RegionFactory> lbuffer(new RegionFactory(lImage));
    unique_ptr<RegionFactory> rbuffer(new RegionFactory(rImage));
    unique_ptr<RegionBase> rregion(rbuffer->createRegion(size, size));
    unique_ptr<RegionBase> lregion(lbuffer->createRegion(size, size));
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

    cout << "Cnt:" << cnt << " Cnt2:" << cnt2 << endl;
    EXPECT_EQ(cnt, cnt2);
}
