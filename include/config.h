#pragma once
#include <cstdint>
#include <string>

#define FULLHD_HEIGHT   200
#define FULLHD_WIDTH    500

#define FRAME   2

#define DATA_HEIGHT (FULLHD_HEIGHT + 2 * FRAME)
#define DATA_WIDTH  (FULLHD_WIDTH + 2 * FRAME)

#define IMAGE_COMPONENT 4

#define STORAGE_SIZE 1920*1240*10

class Configuration
{
    private:
        static double _jacardThreshold;
        static uint32_t _similarityThreshold;
        static constexpr uint8_t _component = 1;
        static constexpr uint8_t _frame = 2;
        static constexpr uint32_t _height = 200;
        static constexpr uint32_t _width = 500;
        static constexpr uint8_t _storageSize = 20;

        Configuration() {}

    public:
        static double getJacardThreshold();

        static uint32_t getSimilarityThreshold();

        static constexpr uint8_t getImageComponent() {
            return _component;
        }

        static constexpr uint8_t getImageFrame() {
            return _frame;
        }

        static constexpr uint32_t getImageHeight() {
            return _height;
        }

        static constexpr uint32_t getImageWidth() {
            return _width;
        }

        static constexpr uint8_t getStorageSize() {
            return _storageSize;
        }

        static std::string toString();

        Configuration(Configuration const&) = delete;
        void operator=(Configuration const&) = delete;

};
