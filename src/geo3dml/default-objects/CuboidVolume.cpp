// UTF-8编码
#include "CuboidVolume.h"

using namespace geo3dml::geometry;

CuboidVolume::CuboidVolume() {

}

CuboidVolume::~CuboidVolume() {

}

int CuboidVolume::AppendVertex(double x, double y, double z) {
    vertices_.emplace_back(Point3D(x, y, z));
    return vertices_.size() - 1;
}

int CuboidVolume::GetVertexCount() const {
    return vertices_.size();
}

bool CuboidVolume::GetVertexAt(int i, double& x, double& y, double& z) const {
    const Point3D& pt = vertices_.at(i);
    x = pt.x;
    y = pt.y;
    z = pt.z;
    return true;
}

int CuboidVolume::AppendCuboid(int v1, int v2, int v3, int v4, int v5, int v6, int v7, int v8) {
    Cuboid cuboid;
    cuboid.vertexIndices[0] = v1;
    cuboid.vertexIndices[1] = v2;
    cuboid.vertexIndices[2] = v3;
    cuboid.vertexIndices[3] = v4;
    cuboid.vertexIndices[4] = v5;
    cuboid.vertexIndices[5] = v6;
    cuboid.vertexIndices[6] = v7;
    cuboid.vertexIndices[7] = v8;
    cuboids_.emplace_back(cuboid);
    return cuboids_.size() - 1;
}

int CuboidVolume::GetCuboidCount() const {
    return cuboids_.size();
}

bool CuboidVolume::GetCuboidAt(int i, int& v1, int& v2, int& v3, int& v4, int& v5, int& v6, int& v7, int& v8) const {
    const Cuboid& cuboid = cuboids_.at(i);
    v1 = cuboid.vertexIndices[0];
    v2 = cuboid.vertexIndices[1];
    v3 = cuboid.vertexIndices[2];
    v4 = cuboid.vertexIndices[3];
    v5 = cuboid.vertexIndices[4];
    v6 = cuboid.vertexIndices[5];
    v7 = cuboid.vertexIndices[6];
    v8 = cuboid.vertexIndices[7];
    return true;
}

geo3dml::Box3D CuboidVolume::GetMinimumBoundingRectangle() const {
    geo3dml::Box3D box;
    for (auto citor = vertices_.cbegin(); citor != vertices_.cend(); ++citor) {
        box.ExtendWith(*citor);
    }
    return box;
}
