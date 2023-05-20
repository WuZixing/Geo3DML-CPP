// UTF-8编码
#include <cmath>
#include <cstring>
#include <geo3dml/Math.h>
#include <geo3dml/Utils.h>

using namespace geo3dml;

Vector3D::Vector3D(double x, double y, double z) : x_(x), y_(y), z_(z) {
    
}

Vector3D::Vector3D(const Vector3D& v) {
    x_ = v.X();
    y_ = v.Y();
    z_ = v.Z();
}

Vector3D::~Vector3D() {

}

Vector3D& Vector3D::operator=(const Vector3D& v) {
    if (this == &v) {
        return *this;
    }
    x_ = v.X();
    y_ = v.Y();
    z_ = v.Z();
    return *this;
}

double Vector3D::X() const {
    return x_;
}

double Vector3D::Y() const {
    return y_;
}

double Vector3D::Z() const {
    return z_;
}

Vector3D& Vector3D::X(double x) {
    x_ = x;
    return *this;
}

Vector3D& Vector3D::Y(double y) {
    y_ = y;
    return *this;
}

Vector3D& Vector3D::Z(double z) {
    z_ = z;
    return *this;
}

double Vector3D::LengthSquared() const {
    return std::pow(x_, 2) + std::pow(y_, 2) + std::pow(z_, 2);
}

double Vector3D::Length() const {
    return std::sqrt(LengthSquared());
}

Vector3D Vector3D::UnitVector() const {
    double len = Length();
    if (IsZero(len)) {
        return Vector3D();
    }
    return Vector3D(x_ / len, y_ / len, z_ / len);
}


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
