// UTF-8编码
#include "TriangularPrismVolume.h"

using namespace geo3dml::geometry;

TriangularPrismVolume::TriangularPrismVolume() {

}

TriangularPrismVolume::~TriangularPrismVolume() {

}

int TriangularPrismVolume::AppendVertex(double x, double y, double z) {
    vertices_.emplace_back(Point3D(x, y, z));
    return vertices_.size() - 1;
}

int TriangularPrismVolume::GetVertexCount() const {
    return vertices_.size();
}

bool TriangularPrismVolume::GetVertexAt(int i, double& x, double& y, double& z) const {
    const Point3D& pt = vertices_.at(i);
    x = pt.x;
    y = pt.y;
    z = pt.z;
    return true;
}

int TriangularPrismVolume::AppendPrism(int top1, int top2, int top3, int bottom1, int bottom2, int bottom3) {
    Prism prism;
    prism.bottomTriangle.v1 = bottom1;
    prism.bottomTriangle.v2 = bottom2;
    prism.bottomTriangle.v3 = bottom3;
    prism.topTriangle.v1 = top1;
    prism.topTriangle.v2 = top2;
    prism.topTriangle.v3 = top3;
    prisms_.emplace_back(prism);
    return prisms_.size() - 1;
}

int TriangularPrismVolume::GetPrismCount() const {
    return prisms_.size();
}

bool TriangularPrismVolume::GetPrismAt(int i, int& top1, int& top2, int& top3, int& bottom1, int& bottom2, int& bottom3) const {
    const Prism& prism = prisms_.at(i);
    top1 = prism.topTriangle.v1;
    top2 = prism.topTriangle.v2;
    top3 = prism.topTriangle.v3;
    bottom1 = prism.bottomTriangle.v1;
    bottom2 = prism.bottomTriangle.v2;
    bottom3 = prism.bottomTriangle.v3;
    return true;
}

geo3dml::Box3D TriangularPrismVolume::GetMinimumBoundingRectangle() const {
    geo3dml::Box3D box;
    for (auto citor = vertices_.cbegin(); citor != vertices_.cend(); ++citor) {
        box.ExtendWith(*citor);
    }
    return box;
}
