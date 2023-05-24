#include "matrices.h"



int main() {
    int list[] = {1, 2, 3, 4, 5, 6};
    Matrix<int> a(2, 3, list);

    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 3; ++j)
            std::cout << "Element (" << i << ", " << j << "): " << a.get_element(i, j) << std::endl;
    }

    return EXIT_SUCCESS;
}