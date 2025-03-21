// UTF-8编码
#include "Point.h"

using namespace geo3dml::geometry;

Point::Point() {
    x_ = 0;
    y_ = 0;
    z_ = 0;
}

Point::~Point() {

}

void Point::SetPosition(double x, double y, double z) {
    x_ = x;
    y_ = y;
    z_ = z;
}

void Point::GetPosition(double& x, double& y, double& z) const {
    x = x_;
    y = y_;
    z = z_;
}

double Point::GetX() const {
    return x_;
}

double Point::GetY() const {
    return y_;
}

double Point::GetZ() const {
    return z_;
}

geo3dml::Box3D Point::GetMinimumBoundingRectangle() const {
    return geo3dml::Box3D(geo3dml::Point3D(x_, y_, z_), geo3dml::Point3D(x_, y_, z_));
}
