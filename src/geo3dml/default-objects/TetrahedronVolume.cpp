// UTF-8编码
#include "TetrahedronVolume.h"

using namespace geo3dml::geometry;

TetrahedronVolume::TetrahedronVolume() {

}

TetrahedronVolume::~TetrahedronVolume() {

}

int TetrahedronVolume::AppendVertex(double x, double y, double z) {
    vertices_.emplace_back(Point3D(x, y, z));
    return vertices_.size() - 1;
}

int TetrahedronVolume::GetVertexCount() const {
    return vertices_.size();
}

bool TetrahedronVolume::GetVertexAt(int i, double& x, double& y, double& z) const {
    const Point3D& pt = vertices_.at(i);
    x = pt.x;
    y = pt.y;
    z = pt.z;
    return true;
}

int TetrahedronVolume::AppendTetrahedron(int v1, int v2, int v3, int v4) {
    cells_.emplace_back(Tetrahedron(v1, v2, v3, v4));
    return cells_.size() - 1;
}

int TetrahedronVolume::GetTetrahedronCount() const {
    return cells_.size();
}

bool TetrahedronVolume::GetTetrahedronAt(int i, int& v1, int& v2, int& v3, int& v4) const {
    const Tetrahedron& cell = cells_.at(i);
    v1 = cell.v1;
    v2 = cell.v2;
    v3 = cell.v3;
    v4 = cell.v4;
    return true;
}

geo3dml::Box3D TetrahedronVolume::GetMinimumBoundingRectangle() const {
    geo3dml::Box3D box;
    for (auto citor = vertices_.cbegin(); citor != vertices_.cend(); ++citor) {
        box.ExtendWith(*citor);
    }
    return box;
}
