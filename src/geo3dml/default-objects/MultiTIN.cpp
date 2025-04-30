// UTF-8编码
#include "MultiTIN.h"
#include "TIN.h"

using namespace geo3dml::geometry;


MultiTIN::MultiTIN() {

}

MultiTIN::~MultiTIN() {
    for (auto tin : tins_) {
        delete tin;
    }
}

int MultiTIN::AddTIN(const geo3dml::TIN* tin) {
    if (tin == nullptr) {
        return -1;
    }
    geometry::TIN* copy = new geometry::TIN();
    if (copy == nullptr) {
        return -1;
    }
    {
        double x = 0, y = 0, z = 0;
        int vertexNumber = tin->GetVertexCount();
        for (int n = 0; n < vertexNumber; ++n) {
            tin->GetVertexAt(n, x, y, z);
            copy->AppendVertex(x, y, z);
        }
    }
    {
        int v1 = -1, v2 = -1, v3 = -1;
        int triangleNumber = tin->GetTriangleCount();
        for (int n = 0; n < triangleNumber; ++n) {
            tin->GetTriangleAt(n, v1, v2, v3);
            copy->AppendTriangle(v1, v2, v3);
        }
    }
    tins_.push_back(copy);
    return tins_.size() - 1;
}

int MultiTIN::GetTINCount() const {
    return tins_.size();
}

int MultiTIN::GetVertexCountOfTIN(int tinIndex) const {
    if (tinIndex >= 0 && tinIndex < tins_.size()) {
        return tins_[tinIndex]->GetVertexCount();
    } else {
        return 0;
    }
}

void MultiTIN::GetVertexOfTIN(int tinIndex, int vertexIndex, double& x, double& y, double& z) const {
    tins_[tinIndex]->GetVertexAt(vertexIndex, x, y, z);
}

int MultiTIN::GetTriangleCountOfTIN(int tinIndex) const {
    if (tinIndex >= 0 && tinIndex < tins_.size()) {
        return tins_[tinIndex]->GetTriangleCount();
    } else {
        return 0;
    }
}

void MultiTIN::GetTriangleOfTIN(int tinIndex, int triangleIndex, int& v1, int& v2, int& v3) const {
    tins_[tinIndex]->GetTriangleAt(triangleIndex, v1, v2, v3);
}

geo3dml::Box3D MultiTIN::GetMinimumBoundingRectangle() const {
    geo3dml::Box3D box;
    for (auto citor = tins_.cbegin(); citor != tins_.cend(); ++citor) {
        box.UnionWith((*citor)->GetMinimumBoundingRectangle());
    }
    return box;
}
