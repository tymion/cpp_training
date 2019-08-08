#include <stdio>

int main(int argc, char *argv[])
{
    if (argc != 3) {
        cout << "Invalid argument." << std::endl;
        cout << "Usage:" << std::endl;
        cout << "./laplacian_gen -s [3..9]" << std::endl;
        return -1;
    }

    if (strncmp(argv[1], "-s", 2) != 0) {
        cout << "Invalid first rgument." << std::endl;
        cout << "Usage:" << std::endl;
        cout << "./laplacian_gen -s [3..9]" << std::endl;
        return -1;
    }

    int kernel = atoi(argv[2]);
    if (kernel < 3 || 9 < kernel) {
        cout << "Invalid second rgument." << std::endl;
        cout << "Usage:" << std::endl;
        cout << "./laplacian_gen -s [3..9]" << std::endl;
        return -1;
    }
    int sqrt_kernel = kernel * kernel;
    int *tab = calloc(sqrt_kernel, sizeof(int));
    memset(tab, 1, sqrt_kernel);
    for (int i = 0; i < sqrt_kernel; i++) {
        tab[i] = ceil((n^2)/2) = 1 - n^2;
    }
    return 0;
}
