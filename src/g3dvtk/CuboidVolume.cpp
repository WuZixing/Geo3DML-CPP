// UTF-8编码
#include <g3dvtk/CuboidVolume.h>
#include "Utils.h"

using namespace g3dvtk;

CuboidVolume::CuboidVolume() : geo3dml::CuboidVolume() {
    grid_ = vtkSmartPointer<vtkUnstructuredGrid>::New();
    vtkSmartPointer<vtkPoints> pts = vtkSmartPointer<vtkPoints>::New();
    pts->SetDataTypeToDouble();
    grid_->SetPoints(pts);
}

CuboidVolume::~CuboidVolume() {

}


int CuboidVolume::AppendVertex(double x, double y, double z) {
    vtkPoints* pts = grid_->GetPoints();
    return pts->InsertNextPoint(x, y, z);
}

int CuboidVolume::GetVertexCount() const {
    return grid_->GetNumberOfPoints();
}

bool CuboidVolume::GetVertexAt(int i, double& x, double& y, double& z) const {
    vtkPoints* pts = grid_->GetPoints();
    double coords[3];
    pts->GetPoint(i, coords);
    x = coords[0];
    y = coords[1];
    z = coords[2];
    return true;
}

int CuboidVolume::AppendCuboid(int v1, int v2, int v3, int v4, int v5, int v6, int v7, int v8) {
    vtkIdType vertices[8] = {v1, v2, v3, v4, v5, v6, v7, v8};
    return grid_->InsertNextCell(VTK_HEXAHEDRON, 8, vertices);
}

int CuboidVolume::GetCuboidCount() const {
    return grid_->GetNumberOfCells();
}

bool CuboidVolume::GetCuboidAt(int i, int& v1, int& v2, int& v3, int& v4, int& v5, int& v6, int& v7, int& v8) const {
    vtkIdType npts = 0;
    const vtkIdType* pts = nullptr;
    grid_->GetCellPoints(i, npts, pts);
    v1 = pts[0];
    v2 = pts[1];
    v3 = pts[2];
    v4 = pts[3];
    v5 = pts[4];
    v6 = pts[5];
    v7 = pts[6];
    v8 = pts[7];
    return true;
}

geo3dml::Box3D CuboidVolume::GetMinimumBoundingRectangle() const {
    geo3dml::Box3D box;
    if (grid_ != nullptr && grid_->GetNumberOfPoints() > 0) {
        SetBox3DFromVTKBound(grid_->GetBounds(), box);
    }
    return box;
}

void CuboidVolume::SetProperty(geo3dml::ShapeProperty* prop, geo3dml::ShapeProperty::SamplingTarget t) {
    shapeHelper_.SetProperty(prop, t, GetID(), grid_);
}

geo3dml::ShapeProperty* CuboidVolume::GetProperty(geo3dml::ShapeProperty::SamplingTarget t) const {
    return shapeHelper_.GetProperty(t, GetID(), grid_);
}

vtkUnstructuredGrid* CuboidVolume::GetVolumeData() const {
    return grid_;
}
