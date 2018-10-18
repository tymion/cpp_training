#include <iostream>

#define size 7

int main() {
    uint32_t height = 200;
    uint32_t width = 500;
    uint32_t cnt = 0;
    for (uint32_t row = 0; row < height - size; row++) {
        for (uint32_t col = 0; col < width - size; col++) {
            uint32_t s_row = (int32_t) row - 3 < 0 ? 0 : (int32_t) row - 3;
            uint32_t s_row_max = row + 3 > height - size ? height - size : row + 3;
            for (; s_row < s_row_max; s_row++) {
                for (uint32_t s_col = col; s_col < width - size; s_col++) {
                    cnt++;
                }
            }
        }
    }
    std::cout << "Cout:" << cnt << std::endl;
    return 0;
}
