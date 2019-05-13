#pragma once
#include <cstdint>
#include <string>

#define FULLHD_HEIGHT   1920
#define FULLHD_WIDTH    1080

#define FRAME   2

#define DATA_HEIGHT (FULLHD_HEIGHT + 2 * FRAME)
#define DATA_WIDTH  (FULLHD_WIDTH + 2 * FRAME)

#define IMAGE_COMPONENT 4

class Configuration
{
    private:
        double _jacardThreshold;
        uint32_t _similarityThreshold;
        static constexpr uint8_t _frame = 0;
        static constexpr uint8_t _storageSize = 10;

        Configuration() {}

    public:
        static Configuration& getInstance();

        static double getJacardThreshold();
        static void setJacardThreshold(double new_threshold);

        static uint32_t getSimilarityThreshold();
        static void setSimilarityThreshold(uint32_t new_threshold);

        static constexpr uint8_t getImageFrame() {
            return _frame;
        }

        static constexpr uint8_t getStorageSize() {
            return _storageSize;
        }

        static std::string toString();

        Configuration(Configuration const&) = delete;
        void operator=(Configuration const&) = delete;

};
