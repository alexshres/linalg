#include "matrices.h"


int main() {
    int list[] = {1, 2, 3, 4, 5, 6};
    Matrix<int> a(2, 3, list);

    std::cout << "MATRIX A: " << std::endl;
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 3; ++j)
            std::cout << "Element (" << i << ", " << j << "): " << a.get_element(i, j) << std::endl;
    }

    std::cout << std::endl;

    Matrix<int> b(a);
    std::cout << "MATRIX B: " << std::endl;
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 3; ++j)
            std::cout << "Element (" << i << ", " << j << "): " << b.get_element(i, j) << std::endl;
    }

    Matrix<int> c(3, 2, list);

    Matrix<int> d = a * c;

    std::cout << "MATRIX D after MATMUL: " << std::endl;
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 3; ++j)
            std::cout << "Element (" << i << ", " << j << "): " << d.get_element(i, j) << std::endl;
    }

    return EXIT_SUCCESS;
}