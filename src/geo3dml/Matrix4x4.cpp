// UTF-8编码
#include <cstring>
#include <geo3dml/Matrix4x4.h>
#include <geo3dml/Matrix3x3.h>

using namespace geo3dml;


Matrix4x4::Matrix4x4() {
    Identify();
}

Matrix4x4::Matrix4x4(const Matrix4x4& m) {
    for (int i = 0; i < 16; ++i) {
        matrix_[i] = m.matrix_[i];
    }
}

Matrix4x4::~Matrix4x4() {

}

Matrix4x4& Matrix4x4::operator=(const Matrix4x4& m) {
    if (this == &m) {
        return *this;
    }
    for (int i = 0; i < 16; ++i) {
        matrix_[i] = m.matrix_[i];
    }
    return *this;
}

Matrix4x4& Matrix4x4::Identify() {
    std::memset(matrix_, 0, sizeof(double) * 16);
    matrix_[0] = 1;
    matrix_[5] = 1;
    matrix_[10] = 1;
    matrix_[15] = 1;
    return *this;
}

Matrix4x4& Matrix4x4::Element(int row, int col, double v) {
    if (row >= 1 && row <= 4 && col >= 1 && col <= 4) {
        matrix_[(row - 1) * 4 + (col - 1)] = v;
    }
    return *this;
}

double Matrix4x4::Element(int row, int col) const {
    if (row >= 1 && row <= 4 && col >= 1 && col <= 4) {
        return matrix_[(row - 1) * 4 + (col - 1)];
    }
    return 0;
}

double Matrix4x4::Determinant() const {
    Matrix3x3 m;
    for (int r = 1; r < 4; ++r) {
        m.Element(r, 1, Element(r + 1, 2));
        m.Element(r, 2, Element(r + 1, 3));
        m.Element(r, 3, Element(r + 1, 4));
    }
    double a1 = Element(1, 1) * m.Determinant();
    for (int r = 1; r < 4; ++r) {
        m.Element(r, 1, Element(r + 1, 1));
        m.Element(r, 2, Element(r + 1, 3));
        m.Element(r, 3, Element(r + 1, 4));
    }
    double a2 = -Element(1, 2) * m.Determinant();
    for (int r = 1; r < 4; ++r) {
        m.Element(r, 1, Element(r + 1, 1));
        m.Element(r, 2, Element(r + 1, 2));
        m.Element(r, 3, Element(r + 1, 4));
    }
    double a3 = Element(1, 3) * m.Determinant();
    for (int r = 1; r < 4; ++r) {
        m.Element(r, 1, Element(r + 1, 1));
        m.Element(r, 2, Element(r + 1, 2));
        m.Element(r, 3, Element(r + 1, 3));
    }
    double a4 = -Element(1, 4) * m.Determinant();
    return a1 + a2 + a3 + a4;
}
