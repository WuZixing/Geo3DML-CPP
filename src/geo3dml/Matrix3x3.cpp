// UTF-8编码
#include <cstring>
#include <geo3dml/Matrix3x3.h>

using namespace geo3dml;

Matrix3x3::Matrix3x3() {
    Identify();
}

Matrix3x3::Matrix3x3(const Matrix3x3& m) {
    for (int i = 0; i < 9; ++i) {
        matrix_[i] = m.matrix_[i];
    }
}

Matrix3x3::~Matrix3x3() {

}

Matrix3x3& Matrix3x3::operator=(const Matrix3x3& m) {
    if (this == &m) {
        return *this;
    }
    for (int i = 0; i < 9; ++i) {
        matrix_[i] = m.matrix_[i];
    }
    return *this;
}

Matrix3x3& Matrix3x3::Identify() {
    std::memset(matrix_, 0, sizeof(double) * 9);
    matrix_[0] = 1;
    matrix_[4] = 1;
    matrix_[8] = 1;
    return *this;
}

Matrix3x3& Matrix3x3::Element(int row, int col, double v) {
    if (row >= 1 && row <= 3 && col >= 1 && col <= 3) {
        matrix_[(row - 1) * 3 + (col - 1)] = v;
    }
    return *this;
}

double Matrix3x3::Element(int row, int col) const {
    if (row >= 1 && row <= 3 && col >= 1 && col <= 3) {
        return matrix_[(row - 1) * 3 + (col - 1)];
    }
    return 0;
}

double Matrix3x3::Determinant() const {
    double a1 = matrix_[0] * (matrix_[4] * matrix_[8] - matrix_[5] * matrix_[7]);
    double a2 = -matrix_[1] * (matrix_[3] * matrix_[8] - matrix_[5] * matrix_[6]);
    double a3 = matrix_[2] * (matrix_[3] * matrix_[7] - matrix_[4] * matrix_[6]);
    return a1 + a2 + a3;
}
