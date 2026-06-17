#include <vector>
#include <stdlib.h>
#include <iostream>
#include <algorithm>
template <class T>
class Matrix {
public:
    int rows, cols;
    T** data;
    std::vector<std::vector<T>> mat;

    Matrix(int r, int c) : rows(r), cols(c) {
        data = new T*[rows];
        for (int i = 0; i < rows; i++) {
            data[i] = new T[cols];
        }
        for (int i = 0; i < rows; i++)
            for (int j = 0; j < cols; j++) {
            mat[i].resize(rows);
            mat[j].resize(cols);
        }
    }
    ~Matrix() {
        for (int i = 0; i < rows; i++) {
            delete[] data[i];
        }
        delete[] data;
    }

    void input() {
        std::cout << "Enter elements of the matrix (" << rows << "x" << cols << "):\n";
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                std::cin >> data[i][j];
            }
        }
    }
    void print() const {
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                std::cout << data[i][j] << "\t";
            }
            std::cout << "\n";
        }
    }
    T Sum() const {
        T sum = 0;
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                sum += data[i][j];
            }
        }
        return sum;
    }
    T Max() const {
        T max = data[0][0];
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                if (data[i][j] > max) {
                    max = data[i][j];
                }
            }
        }
        return max;
    }
};