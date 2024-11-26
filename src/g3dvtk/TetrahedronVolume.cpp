// UTF-8编码
#include <g3dvtk/TetrahedronVolume.h>
#include "Utils.h"

using namespace g3dvtk;

TetrahedronVolume::TetrahedronVolume() : geo3dml::TetrahedronVolume() {
    grid_ = vtkSmartPointer<vtkUnstructuredGrid>::New();
    vtkSmartPointer<vtkPoints> pts = vtkSmartPointer<vtkPoints>::New();
    pts->SetDataTypeToDouble();
    grid_->SetPoints(pts);
}

TetrahedronVolume::~TetrahedronVolume() {

}

int TetrahedronVolume::AppendVertex(double x, double y, double z) {
    vtkPoints* pts = grid_->GetPoints();
    return pts->InsertNextPoint(x, y, z);
}

int TetrahedronVolume::GetVertexCount() const {
    return grid_->GetNumberOfPoints();
}

bool TetrahedronVolume::GetVertexAt(int i, double& x, double& y, double& z) const {
    vtkPoints* pts = grid_->GetPoints();
    double coords[3];
    pts->GetPoint(i, coords);
    x = coords[0];
    y = coords[1];
    z = coords[2];
    return true;
}

int TetrahedronVolume::AppendTetrahedron(int v1, int v2, int v3, int v4) {
    vtkIdType vertices[4];
    vertices[0] = v1;
    vertices[1] = v2;
    vertices[2] = v3;
    vertices[3] = v4;
    return grid_->InsertNextCell(VTK_TETRA, 4, vertices);
}

int TetrahedronVolume::GetTetrahedronCount() const {
    return grid_->GetNumberOfCells();
}

bool TetrahedronVolume::GetTetrahedronAt(int i, int& v1, int& v2, int& v3, int& v4) const {
    vtkIdType npts = 0;
    const vtkIdType* pts = nullptr;
    grid_->GetCellPoints(i, npts, pts);
    v1 = pts[0];
    v2 = pts[1];
    v3 = pts[2];
    v4 = pts[3];
    return true;
}

vtkUnstructuredGrid* TetrahedronVolume::GetVolumeData() const {
    return grid_;
}

geo3dml::Box3D TetrahedronVolume::GetMinimumBoundingRectangle() const {
    geo3dml::Box3D box;
    if (grid_ != nullptr && grid_->GetNumberOfPoints() > 0) {
        SetBox3DFromVTKBound(grid_->GetBounds(), box);
    }
    return box;
}

void TetrahedronVolume::SetProperty(geo3dml::ShapeProperty* prop, geo3dml::ShapeProperty::SamplingTarget t) {
    shapeHelper_.SetProperty(prop, t, GetID(), grid_);
}

geo3dml::ShapeProperty* TetrahedronVolume::GetProperty(geo3dml::ShapeProperty::SamplingTarget t) const {
    return shapeHelper_.GetProperty(t, GetID(), grid_);
}
