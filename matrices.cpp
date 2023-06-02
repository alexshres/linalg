#include "matrices.h"

//TODO: returns upper triangular matrix
Matrix<double> gauss_jordan(const Matrix<double> &source);

int main() {
    int list[] = {1, 2, 3, 4, 5, 6};
    Matrix<int> a(2, 3, list);

    std::cout << "MATRIX A: " << std::endl;
    for (int i = 0; i < a.get_num_rows(); ++i) {
        for (int j = 0; j < a.get_num_cols(); ++j)
            std::cout << "Element (" << i << ", " << j << "): " << a.get_element(i, j) << std::endl;
    }

    std::cout << std::endl;

    Matrix<int> b(3, 2, list);
    std::cout << "MATRIX B: " << std::endl;
    for (int i = 0; i < b.get_num_rows(); ++i) {
        for (int j = 0; j < b.get_num_cols(); ++j)
            std::cout << "Element (" << i << ", " << j << "): " << b.get_element(i, j) << std::endl;
    }

    Matrix<int> c = a * b;

    std::cout << "MATRIX C after MATMUL: " << std::endl;
    for (int i = 0; i < c.get_num_cols(); ++i) {
        for (int j = 0; j < c.get_num_rows(); ++j)
            std::cout << "Element (" << i << ", " << j << "): " << c.get_element(i, j) << std::endl;
    }

    return EXIT_SUCCESS;
}