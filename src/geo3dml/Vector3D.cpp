// UTF-8编码
#include <cmath>
#include <geo3dml/Vector3D.h>
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

