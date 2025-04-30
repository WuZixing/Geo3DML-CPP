// UTF-8编码
#include <g3dvtk/MultiTIN.h>
#include "Utils.h"

using namespace g3dvtk;

MultiTIN::MultiTIN() {
    polyData_ = vtkSmartPointer<vtkPolyData>::New();
    vtkSmartPointer<vtkPoints> pts = vtkSmartPointer<vtkPoints>::New();
    pts->SetDataTypeToDouble();
    vtkSmartPointer<vtkCellArray> polys = vtkSmartPointer<vtkCellArray>::New();
    polyData_->SetPoints(pts);
    polyData_->SetPolys(polys);
}

MultiTIN::~MultiTIN() {

}

int MultiTIN::AddTIN(const geo3dml::TIN* tin) {
    if (tin == nullptr) {
        return -1;
    }
    // 添加顶点
    int vertexNumber = tin->GetVertexCount();
    tinVertices_.push_back(std::vector<vtkIdType>());
    auto tinVertices = tinVertices_.rbegin();
    tinVertices->reserve(vertexNumber);
    vtkPoints* pts = polyData_->GetPoints();
    double x = 0, y = 0, z = 0;
    for (int n = 0; n < vertexNumber; ++n) {
        tin->GetVertexAt(n, x, y, z);
        vtkIdType ptIndex = pts->InsertNextPoint(x, y, z);
        tinVertices->push_back(ptIndex);
    }
    // 添加三角形
    int triangleNumber = tin->GetTriangleCount();
    tinTriangles_.push_back(std::vector<Triangle>());
    auto tinTriangles = tinTriangles_.rbegin();
    tinTriangles->reserve(triangleNumber);
    int v1 = -1, v2 = -1, v3 = -1;
    vtkIdType vertices[3] = {-1, -1, -1};
    for (int n = 0; n < triangleNumber; ++n) {
        tin->GetTriangleAt(n, v1, v2, v3);
        vertices[0] = tinVertices->at(v1);
        vertices[1] = tinVertices->at(v2);
        vertices[2] = tinVertices->at(v3);
        vtkIdType triangleIndex = polyData_->InsertNextCell(VTK_TRIANGLE, 3, vertices);
        tinTriangles->push_back(Triangle(v1, v2, v3));
    }
    return tinVertices_.size() - 1;
}

int MultiTIN::GetTINCount() const {
    return tinVertices_.size();
}

int MultiTIN::GetVertexCountOfTIN(int tinIndex) const {
    return tinVertices_[tinIndex].size();
}

void MultiTIN::GetVertexOfTIN(int tinIndex, int vertexIndex, double& x, double& y, double& z) const {
    vtkIdType ptIndex = tinVertices_[tinIndex][vertexIndex];
    double coords[3] = {0, 0, 0};
    polyData_->GetPoints()->GetPoint(ptIndex, coords);
    x = coords[0];
    y = coords[1];
    z = coords[2];
}

int MultiTIN::GetTriangleCountOfTIN(int tinIndex) const {
    return tinTriangles_[tinIndex].size();
}

void MultiTIN::GetTriangleOfTIN(int tinIndex, int triangleIndex, int& v1, int& v2, int& v3) const {
    const Triangle& triangle = tinTriangles_[tinIndex][triangleIndex];
    v1 = triangle.v1;
    v2 = triangle.v2;
    v3 = triangle.v3;
}

geo3dml::Box3D MultiTIN::GetMinimumBoundingRectangle() const {
    geo3dml::Box3D box;
    if (polyData_ != nullptr && polyData_->GetNumberOfPoints() > 0) {
        SetBox3DFromVTKBound(polyData_->GetBounds(), box);
    }
    return box;
}

void MultiTIN::SetProperty(geo3dml::ShapeProperty* prop, geo3dml::ShapeProperty::SamplingTarget t) {
    shapeHelper_.SetProperty(prop, t, GetID(), polyData_);
}

geo3dml::ShapeProperty* MultiTIN::GetProperty(geo3dml::ShapeProperty::SamplingTarget t) const {
    return shapeHelper_.GetProperty(t, GetID(), polyData_);
}

vtkPolyData* MultiTIN::GetPolyData() const {
    return polyData_.Get();
}
