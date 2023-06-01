#ifndef LINALG_MATRICES_H
#define LINALG_MATRICES_H

// NOTE:
// when using templates, all definitions of a class are
// included in the header file
#include <iostream>
#include <cstdlib>

template<class T>
class Matrix {
public:
    // CONSTRUCTORS
    Matrix(); // Default
    Matrix(int num_rows, int num_cols); // Rows and columns set
    Matrix(int num_rows, int num_cols, const T *input_data); // Rows and columns and an array set
    Matrix(const Matrix<T> &input_matrix); // Copy constructor

    // Destructor
    ~Matrix();

    // Config methods
    bool resize(int num_rows, int num_cols);

    // Element access methods
    T get_element(int row, int col);

    bool set_element(int row, int col, T element_value);

    int get_num_rows() const;

    int get_num_cols() const;

    // Overloading operators
    bool operator==(const Matrix<T> &rhs);

    // Overloading +, - and * operators (friends).
    template<class U>
    friend Matrix<U> operator+(const Matrix<U> &lhs, const Matrix<U> &rhs);

    template<class U>
    friend Matrix<U> operator+(const U &lhs, const Matrix<U> &rhs);

    template<class U>
    friend Matrix<U> operator+(const Matrix<U> &lhs, const U &rhs);

    template<class U>
    friend Matrix<U> operator-(const Matrix<U> &lhs, const Matrix<U> &rhs);

    template<class U>
    friend Matrix<U> operator-(const U &lhs, const Matrix<U> &rhs);

    template<class U>
    friend Matrix<U> operator-(const Matrix<U> &lhs, const U &rhs);

    template<class U>
    friend Matrix<U> operator*(const Matrix<U> &lhs, const Matrix<U> &rhs); // dot product

    template<class U>
    friend Matrix<U> operator*(const U &lhs, const Matrix<U> &rhs); // scalar product

    template<class U>
    friend Matrix<U> operator*(const Matrix<U> &lhs, const U &rhs);  // scalar product

private:
    int sub_to_index(int row, int col);

private:
    T *linear_matrix;
    int n_rows, n_cols, n_elements;

};


/* *************************************************
CONSTRUCTOR / DESTRUCTOR FUNCTIONS
************************************************  */

template<class T>
Matrix<T>::Matrix() {
    n_rows = 1;
    n_cols = 1;
    n_elements = 1;

    linear_matrix = new T[n_elements];
    linear_matrix[0] = 0.0;
}

template<class T>
Matrix<T>::Matrix(int num_rows, int num_cols) {
    n_rows = num_rows;
    n_cols = num_cols;
    n_elements = num_cols * num_rows;

    linear_matrix = new T[n_elements];

    for (int i = 0; i < n_elements; i++)
        linear_matrix[i] = 0.0;
}

template<class T>
Matrix<T>::Matrix(int num_rows, int num_cols, const T *input_data) {
    n_rows = num_rows;
    n_cols = num_cols;
    n_elements = num_rows * num_cols;

    linear_matrix = new T[n_elements];

    for (int i = 0; i < n_elements; i++)
        linear_matrix[i] = input_data[i];
}

template<class T>
Matrix<T>::Matrix(const Matrix<T> &input_matrix) {
    n_rows = input_matrix.get_num_rows();
    n_cols = input_matrix.get_num_cols();
    n_elements = n_rows * n_cols;

    linear_matrix = new T[n_elements];
    for (int i = 0; i < n_elements; i++)
        linear_matrix[i] = input_matrix.linear_matrix[i];
}

template<class T>
Matrix<T>::~Matrix() {
    if (linear_matrix != nullptr)
        delete[] linear_matrix;
}


// does not copy the elements over
template<class T>
bool Matrix<T>::resize(int num_rows, int num_cols) {
    n_rows = num_rows;
    n_cols = num_cols;
    n_elements = (n_rows * n_cols);

    delete[] linear_matrix;

    linear_matrix = new T[n_elements];
    if (linear_matrix != nullptr) {
        for (int i = 0; i < n_elements; i++)
            linear_matrix[i] = 0.0;

        return true;
    }

    return false;
}

/* *************************************************
Element Functions
************************************************ */

template<class T>
T Matrix<T>::get_element(int row, int col) {
    int lin_idx = sub_to_index(row, col);
    if (lin_idx >= 0)
        return linear_matrix[lin_idx];

    return -1;
}

template<class T>
bool Matrix<T>::set_element(int row, int col, T element_value) {
    int lin_idx = sub_to_index(row, col);
    if (lin_idx >= 0) {
        linear_matrix[lin_idx] = element_value;
        return true;
    } else {
        return false;
    }
}

template<class T>
int Matrix<T>::get_num_cols() const {
    return n_cols;
}

template<class T>
int Matrix<T>::get_num_rows() const {
    return n_rows;
}

//template<class T>
//bool Matrix<T>::operator==(const Matrix<T> &rhs) {
//
//}

template<class T>
Matrix<T> operator+(const Matrix<T> &lhs, const Matrix<T> &rhs) {
    // assuming both matrices are of the same size
    // TODO update so there are conditions to pass before adding

    int num_rows = lhs.n_rows;
    int num_cols = lhs.n_cols;

    int num_elements = num_cols * num_rows;

    T *temp_result = new T[num_elements];

    for (int i = 0; i < num_elements; i++)
        temp_result[i] = lhs.linear_matrix[i] + rhs.linear_matrix[i];

    Matrix<T> result(num_rows, num_cols, temp_result);
    delete[] temp_result;

    return result;
}

template<class T>
Matrix<T> operator+(const T &lhs, const Matrix<T> &rhs) {
    int new_row = rhs.n_rows;
    int new_col = rhs.n_cols;

    int num_elements = new_row * new_col;
    T *temp_result = new T[num_elements];

    for (int i = 0; i < num_elements; i++) {
        temp_result[i] = rhs.linear_matrix[i] + lhs;
    }

    Matrix<T> result(new_row, new_col, temp_result);
    delete[] temp_result;

    return result;
}

template<class T>
Matrix<T> operator+(const Matrix<T> &lhs, const T &rhs) {
    int new_rows = lhs.n_rows;
    int new_cols = lhs.n_cols;
    int num_elements = new_rows * new_cols;

    T *temp_result = new T[num_elements];

    for (int i = 0; i < num_elements; i++)
        temp_result[i] = lhs.linear_matrix[i] + rhs;

    Matrix<T> result(new_rows, new_cols, temp_result);
    delete[] temp_result;

    return result;
}

template<class T>
Matrix<T> operator-(const Matrix<T> &lhs, const Matrix<T> &rhs) {
    // assuming both matrices are of the same size
    // TODO update so there are conditions to pass before adding

    int num_rows = lhs.n_rows;
    int num_cols = lhs.n_cols;

    int num_elements = num_cols * num_rows;

    T *temp_result = new T[num_elements];

    for (int i = 0; i < num_elements; i++)
        temp_result[i] = lhs.linear_matrix[i] - rhs.linear_matrix[i];

    Matrix<T> result(num_rows, num_cols, temp_result);
    delete[] temp_result;

    return result;
}

template<class T>
Matrix<T> operator-(const T &lhs, const Matrix<T> &rhs) {
    int new_row = rhs.n_rows;
    int new_col = rhs.n_cols;

    int num_elements = new_row * new_col;
    T *temp_result = new T[num_elements];

    for (int i = 0; i < num_elements; i++) {
        temp_result[i] = rhs.linear_matrix[i] - lhs;
    }

    Matrix<T> result(new_row, new_col, temp_result);
    delete[] temp_result;

    return result;
}

template<class T>
Matrix<T> operator-(const Matrix<T> &lhs, const T &rhs) {
    int new_rows = lhs.n_rows;
    int new_cols = lhs.n_cols;
    int num_elements = new_rows * new_cols;

    T *temp_result = new T[num_elements];

    for (int i = 0; i < num_elements; i++)
        temp_result[i] = lhs.linear_matrix[i] - rhs;

    Matrix<T> result(new_rows, new_cols, temp_result);
    delete[] temp_result;

    return result;
}


// TODO dot product
template<class T>
Matrix<T> operator*(const Matrix<T> &lhs, const Matrix<T> &rhs) {
    assert(lhs.n_cols == rhs.n_rows);

//    Matrix<T> result(lhs.get_num_rows(), rhs.get_num_cols());
    T *list_result = new T[lhs.n_rows * rhs.n_cols];

    for (int i = 0; i < lhs.n_cols; ++i) {
        for (int j = 0; j < rhs.n_cols; ++j) {
            T element_value = 0.0;
            for (int k = 0; k < lhs.n_cols; ++k) {
                int lhs_lin_idx = (i * lhs.n_cols) + k;
                int rhs_lin_idx = (k * rhs.n_cols) + j;
                element_value += lhs.linear_matrix[lhs_lin_idx] + rhs.linear_matrix[rhs_lin_idx];
            }

            int result_lin_idx = (i * rhs.n_cols) + j;
            list_result[result_lin_idx] = element_value;
        }
    }

    Matrix<T> result(lhs.get_num_rows(), rhs.get_num_cols(), list_result);
    delete[] list_result;

    return result;
}

// scalar product
template<class T>
Matrix<T> operator*(const T &lhs, const Matrix<T> &rhs) {
    int new_rows = rhs.n_rows;
    int new_cols = rhs.n_cols;
    int num_elements = new_rows * new_cols;

    T *temp_result = new T[num_elements];

    for (int i = 0; i < num_elements; i++)
        temp_result[i] = lhs * rhs.linear_matrix[i];

    Matrix<T> result(new_rows, new_cols, temp_result);
    delete[] temp_result;

    return result;

}

template<class T>
Matrix<T> operator*(const Matrix<T> &lhs, const T &rhs) {
    int new_rows = lhs.n_rows;
    int new_cols = lhs.n_cols;
    int num_elements = new_rows * new_cols;

    T *temp_result = new T[num_elements];

    for (int i = 0; i < num_elements; i++)
        temp_result[i] = rhs * lhs.linear_matrix[i];

    Matrix<T> result(new_rows, new_cols, temp_result);
    delete[] temp_result;

    return result;
}

template<class T>
int Matrix<T>::sub_to_index(int row, int col) {
    return (row * get_num_cols()) + col;
}

template<class T>
bool Matrix<T>::operator==(const Matrix<T> &rhs) {
    if (this->get_num_cols() != rhs.get_num_cols() && this->get_num_rows() != rhs.get_num_cols())
        return false;

    bool result = true;
    for (int i = 0; i < this->n_elements; ++i) {
        if (this->linear_matrix[i] != rhs.linear_matrix[i])
            result = false;
    }

    return result;
}

#endif //LINALG_MATRICES_H
