// UTF-8编码
#include "MultiLineString.h"

using namespace geo3dml::geometry;

MultiLineString::MultiLineString() {

}

MultiLineString::~MultiLineString() {

}

int MultiLineString::AddLineString(const geo3dml::LineString* line) {
    lines_.emplace_back(geometry::LineString());
    Point3D pt;
    auto itor = lines_.rbegin();
    for (int n = 0; n < line->GetVertexCount(); ++n) {
        line->GetVertexAt(n, pt.x, pt.y, pt.z);
        itor->AddVertex(pt.x, pt.y, pt.z);
    }
    return lines_.size() - 1;
}

int MultiLineString::GetLineStringCount() const {
    return lines_.size();
}

int MultiLineString::GetVertexCountOfLineString(int lineIndex) const {
    return lines_[lineIndex].GetVertexCount();
}

void MultiLineString::GetVertexOfLineString(int lineIndex, int vertexIndex, double& x, double& y, double& z) const {
    const auto& line = lines_.at(lineIndex);
    line.GetVertexAt(vertexIndex, x, y, z);
}

geo3dml::Box3D MultiLineString::GetMinimumBoundingRectangle() const {
    geo3dml::Box3D box;
    for (auto citor = lines_.cbegin(); citor != lines_.cend(); ++citor) {
        box.UnionWith(citor->GetMinimumBoundingRectangle());
    }
    return box;
}