#include <iostream>
#include "gtest/gtest.h"
#include "config.h"

class ConfigurationTest : public ::testing::Test
{
    protected:
        virtual void SetUp() {
        }

        virtual void TearDown() {
        }
};

TEST(ConfigurationTest, jacardThreshold)
{
    Configuration::setJacardThreshold(0.1);
    EXPECT_EQ(Configuration::getJacardThreshold(), 0.1);
}

TEST(ConfigurationTest, similarityThreshold)
{
    Configuration::setSimilarityThreshold(99);
    EXPECT_EQ(Configuration::getSimilarityThreshold(), (uint32_t) 99);
}
