// UTF-8编码
#include "TIN.h"

using namespace geo3dml::geometry;

TIN::TIN() {

}

TIN::~TIN() {

}

void TIN::AppendVertex(double x, double y, double z) {
    vertices_.emplace_back(Point3D(x, y, z));
}

int TIN::GetVertexCount() const {
    return vertices_.size();
}

void TIN::GetVertexAt(int i, double& x, double& y, double& z) const {
    const Point3D& pt = vertices_.at(i);
    x = pt.x;
    y = pt.y;
    z = pt.z;
}

void TIN::AppendTriangle(int v1, int v2, int v3) {
    triangles_.emplace_back(Triangle(v1, v2, v3));
}

int TIN::GetTriangleCount() const {
    return triangles_.size();
}

void TIN::GetTriangleAt(int i, int& v1, int& v2, int& v3) const {
    const Triangle& triangle = triangles_.at(i);
    v1 = triangle.v1;
    v2 = triangle.v2;
    v3 = triangle.v3;
}

geo3dml::Box3D TIN::GetMinimumBoundingRectangle() const {
    geo3dml::Box3D box;
    for (auto citor = vertices_.cbegin(); citor != vertices_.cend(); ++citor) {
        box.ExtendWith(*citor);
    }
    return box;
}
