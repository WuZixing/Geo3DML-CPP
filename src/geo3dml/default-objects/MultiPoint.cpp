// UTF-8编码
#include "MultiPoint.h"

using namespace geo3dml::geometry;

MultiPoint::MultiPoint() {

}

MultiPoint::~MultiPoint() {

}

void MultiPoint::AddPoint(double x, double y, double z) {
    points_.emplace_back(Point3D(x, y, z));
}

int MultiPoint::GetPointCount() const {
    return points_.size();
}

void MultiPoint::GetPointAt(int i, double& x, double& y, double& z) const {
    const auto& pt = points_.at(i);
    x = pt.x;
    y = pt.y;
    z = pt.z;
}

geo3dml::Box3D MultiPoint::GetMinimumBoundingRectangle() const {
    geo3dml::Box3D box;
    for (auto citor = points_.cbegin(); citor != points_.cend(); ++citor) {
        box.ExtendWith(*citor);
    }
    return box;
}