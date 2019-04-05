#include <iostream>
#include <cstdio>
#include <cstdint>
#include <random>
#include <ctime>

thread_local std::mt19937 gen{std::random_device{}()};

template<typename T>
T random(T  min, T max) {
    using dist = std::conditional_t<
        std::is_integral<T>::value,
        std::uniform_int_distribution<T>,
        std::uniform_real_distribution<T>
    >;
    return dist{min, max}(gen);
};

#define kernel 8
#define component 4
#define SIZE8 component*kernel*1024
#define SIZE32 kernel*1024

int main(int argc, char *argv[])
{
    uint8_t rgb[SIZE8];
    uint32_t rgb32[SIZE32];
    uint8_t fdata8[SIZE8/kernel] = {0};
    uint32_t fdata32[SIZE32/kernel] = {0};
    uint8_t sdata8[SIZE8/kernel] = {0};
    uint32_t sdata32[SIZE32/kernel] = {0};
    uint32_t data32[SIZE32/kernel] = {0};
    for (uint32_t i = 0; i < SIZE8; i++)
    {
        rgb[i] = random(0, UINT8_MAX);
    }
    for (uint32_t i = 0; i < SIZE32; i++)
    {
        rgb32[i] = rgb[i + 3] | rgb[i + 2] << 8 | rgb[i + 1] << 16 | rgb[i] << 24;
    }

    uint32_t tmp32[component] = {0};
    uint8_t tmp8 = 0;
    uint8_t tmp = 0;
    double duration;
    std::cout.precision(10);
    clock_t start = clock();
    for (uint32_t i = 0; i < SIZE8/kernel/component; i++)
    {
        for (uint8_t j = 0; j < kernel; j++)
        {
            for (uint8_t n = 0; n < component; n++)
            {
                fdata8[i*component + n] += rgb[i*j*component + n]/kernel;
            }
        }
    }
    duration = (clock() - start) / (double) CLOCKS_PER_SEC;
    std::cout << "Time fdata8: "<< duration << std::endl;

    start = clock();
    for (uint32_t i = 0; i < SIZE32/kernel; i++)
    {
        for (uint32_t j = 0; j < kernel; j++)
        {
            fdata32[i] += rgb32[i*kernel + j]/kernel;
        }
    }
    duration = (clock() - start) / (double) CLOCKS_PER_SEC;
    std::cout << "Time fdata32: "<< duration << std::endl;

    start = clock();
    for (uint32_t i = 0; i < SIZE8/kernel/component; i++)
    {
        for (uint32_t j = 0; j < kernel; j++)
        {
            for (uint8_t n = 0; n < component; n++)
            {
                tmp32[n] += rgb[i*j*component + n];
            }
        }
        for (uint8_t n = 0; n < component; n++)
        {
            sdata8[i*component + n] = tmp32[n] / kernel;
            tmp32[n] = 0;
        }
    }
    duration = (clock() - start) / (double) CLOCKS_PER_SEC;
    std::cout << "Time sdata8: "<< duration << std::endl;

    start = clock();
    for (uint32_t i = 0; i < SIZE32/kernel; i++)
    {
        for (uint32_t j = 0; j < kernel; j++)
        {
            tmp32[0] += (rgb32[i*kernel + j] & 0xFF) >> 24;
            tmp32[1] += (rgb32[i*kernel + j] & 0xFF) >> 16;
            tmp32[2] += (rgb32[i*kernel + j] & 0xFF) >> 8;
            tmp32[3] += rgb32[i*kernel + j] & 0xFF;
        }
        sdata32[i] = (((tmp32[0] / kernel) & 0xFF) << 24) |
            (((tmp32[1] / kernel) & 0xFF) << 16) |
            (((tmp32[2] / kernel) & 0xFF) << 8) |
            ((tmp32[3] / kernel) & 0xFF);
        tmp32[0] = 0;
        tmp32[1] = 0;
        tmp32[2] = 0;
        tmp32[3] = 0;
    }
    duration = (clock() - start) / (double) CLOCKS_PER_SEC;
    std::cout << "Time sdata32: "<< duration << std::endl;
    std::cout << std::endl;

    double sumx = 0;
    uint32_t large_cnt = 0;
    for (uint32_t i = 0; i < SIZE8/kernel; i++)
    {
        sumx += ((int) fdata8[i] - (int) sdata8[i]) / (double) sdata8[i];
        if (sdata8[i] > fdata8[i]) {
            large_cnt++;
        }
    }
    sumx /= SIZE8/kernel;
    std::cout << "Avg8:" << sumx << std::endl;
    std::cout << "sdata8 is larger:" << large_cnt << "/" << SIZE8/kernel << std::endl;
    std::cout << std::endl;

    large_cnt = 0;
    sumx = 0;
    for (uint32_t i = 0; i < SIZE32/kernel; i++)
    {
        sumx += ((int) fdata32[i] - (int) sdata32[i]) / (double) sdata32[i];
        if (sdata8[i] > fdata8[i]) {
            large_cnt++;
        }
    }
    sumx /= SIZE32/kernel;
    std::cout << "Avg32:" << sumx << std::endl;
    std::cout << "sdata32 is larger:" << large_cnt << "/" << SIZE32/kernel << std::endl;
    uint32_t val = 2 << 24 | 2 << 16 | 2 << 8 | 2;
    std::cout << "print:" << val << std::endl;
    std::cout << std::endl;

    large_cnt = 0;
    sumx = 0;
    for (uint32_t i = 0; i < SIZE32/kernel; i++)
    {
        tmp = ((sdata8[i] & 0xFF) << 24) |
            ((sdata8[i+1] & 0xFF) << 16) |
            ((sdata8[i+2] & 0xFF) << 8) |
            (sdata8[i+3] & 0xFF);
        sumx += sdata32[i] - tmp;
        if (tmp > sdata32[i]) {
            large_cnt++;
        }
    }
    sumx /= SIZE32/kernel;
    std::cout << "Avg32:" << sumx << std::endl;
    std::cout << "sdata32 is larger:" << large_cnt << "/" << SIZE32/kernel << std::endl;
    return 0;
}
