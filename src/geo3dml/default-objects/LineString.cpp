// UTF-8编码
#include "LineString.h"

using namespace geo3dml::geometry;

LineString::LineString() {

}

LineString::~LineString() {

}

void LineString::AddVertex(double x, double y, double z) {
    vertices_.emplace_back(Point3D(x, y, z));
}

int LineString::GetVertexCount() const {
    return vertices_.size();
}

void LineString::GetVertexAt(int i, double& x, double& y, double& z) const {
    const Point3D& pt = vertices_.at(i);
    x = pt.x;
    y = pt.y;
    z = pt.z;
}

geo3dml::Box3D LineString::GetMinimumBoundingRectangle() const {
    geo3dml::Box3D box;
    for (auto citor = vertices_.cbegin(); citor != vertices_.cend(); ++citor) {
        box.ExtendWith(*citor);
    }
    return box;
}