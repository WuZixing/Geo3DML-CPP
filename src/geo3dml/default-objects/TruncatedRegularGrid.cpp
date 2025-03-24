// UTF-8编码
#include "TruncatedRegularGrid.h"

using namespace geo3dml::geometry;

TruncatedRegularGrid::TruncatedRegularGrid() {

}

TruncatedRegularGrid::~TruncatedRegularGrid() {

}

int TruncatedRegularGrid::AppendVertex(double x, double y, double z) {
    vertices_.emplace_back(Point3D(x, y, z));
    return vertices_.size() - 1;
}

int TruncatedRegularGrid::GetVertexCount() const {
    return vertices_.size();
}

bool TruncatedRegularGrid::GetVertexAt(int i, double& x, double& y, double& z) const {
    const Point3D& pt = vertices_.at(i);
    x = pt.x;
    y = pt.y;
    z = pt.z;
    return true;
}

int TruncatedRegularGrid::AppendFace(const std::list<int>& vertices) {
    Face face;
    face.vertices = vertices;
    faces_.emplace_back(face);
    return faces_.size() - 1;
}

int TruncatedRegularGrid::GetFaceCount() const {
    return faces_.size();
}

bool TruncatedRegularGrid::GetFaceAt(int i, std::list<int>& vertices) const {
    const Face& face = faces_.at(i);
    vertices = face.vertices;
    return true;
}

int TruncatedRegularGrid::AppendCell(const std::list<int>& faces, int i, int j, int k) {
    Cell cell;
    cell.faces = faces;
    cell.i = i;
    cell.j = j;
    cell.k = k;
    cells_.emplace_back(cell);
    return cells_.size() - 1;
}

int TruncatedRegularGrid::GetCellCount() const {
    return cells_.size();
}

bool TruncatedRegularGrid::GetCellAt(int n, std::list<int>& faces, int& i, int& j, int& k) const {
    const Cell& cell = cells_.at(n);
    faces = cell.faces;
    i = cell.i;
    j = cell.j;
    k = cell.k;
    return true;
}

geo3dml::Box3D TruncatedRegularGrid::GetMinimumBoundingRectangle() const {
    geo3dml::Box3D box;
    for (auto citor = vertices_.cbegin(); citor != vertices_.cend(); ++citor) {
        box.ExtendWith(*citor);
    }
    return box;
}
