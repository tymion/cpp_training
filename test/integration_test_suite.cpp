#include <iostream>
#include <cstdio>
#include "gtest/gtest.h"
#include "libpng_wrapper.h"
#include "region.h"
#include "region_factory.h"
#include "loader.h"

using namespace std;

class IntegrationTest : public ::testing::Test
{
    protected:
        virtual void SetUp() {
        }

        virtual void TearDown() {
        }
};

TEST(IntegrationTest, getData)
{
    shared_ptr<IImage> lImage(Loader::loadImage("test/test1.png"));
    shared_ptr<IImage> rImage(Loader::loadImage("test/test2.png"));
    uint32_t size = 7;
    uint32_t height = lImage->getHeight();
    uint32_t width = lImage->getWidth();
    unique_ptr<RegionFactory> lbuffer(new RegionFactory(lImage));
    unique_ptr<RegionFactory> rbuffer(new RegionFactory(rImage));
    unique_ptr<RegionBase> rregion(rbuffer->createRegion(size, size));
    unique_ptr<RegionBase> lregion(lbuffer->createRegion(size, size));
    uint32_t cnt = 0;
    uint32_t cnt1 = 0;
    uint32_t cnt2 = 0;
    double similar = 0;
    Configuration::setSimilarityThreshold(25);
    Configuration::setJacardThreshold(0.5);
    for (uint32_t row = 0; row < height - size; row++) {
        for (uint32_t col = 0; col < width - size; col++) {
            rbuffer->updateRegion(row, col, rregion);
            lbuffer->updateRegion(row, col, lregion);
            if (rregion->compare(*lregion, similar)) {
                cout << "SubStep3:" << similar << endl;
                cnt1++;
            }
            if (*rregion == *lregion) {
                cnt++;
            }
            cnt2++;
        }
    }

    cout << "Cnt:" << cnt << " Cnt1:" <<  cnt1 << " Cnt2:" << cnt2 << endl;
    EXPECT_EQ(cnt, cnt2);
}
