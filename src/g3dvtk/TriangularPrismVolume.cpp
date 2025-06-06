// UTF-8编码
#include <g3dvtk/TriangularPrismVolume.h>
#include <vtkCellArray.h>
#include "Utils.h"

using namespace g3dvtk;

TriangularPrismVolume::TriangularPrismVolume() {
    gridData_ = vtkSmartPointer<vtkUnstructuredGrid>::New();
    vtkSmartPointer<vtkPoints> pts = vtkSmartPointer<vtkPoints>::New();
    pts->SetDataTypeToDouble();
    gridData_->SetPoints(pts);
}

TriangularPrismVolume::~TriangularPrismVolume() {

}

int TriangularPrismVolume::AppendVertex(double x, double y, double z) {
    vtkPoints* pts = gridData_->GetPoints();
    return pts->InsertNextPoint(x, y, z);
}

int TriangularPrismVolume::GetVertexCount() const {
    return gridData_->GetNumberOfPoints();
}

bool TriangularPrismVolume::GetVertexAt(int i, double& x, double& y, double& z) const {
    vtkPoints* pts = gridData_->GetPoints();
    double coords[3];
    pts->GetPoint(i, coords);
    x = coords[0];
    y = coords[1];
    z = coords[2];
    return true;
}

int TriangularPrismVolume::AppendPrism(int top1, int top2, int top3, int bottom1, int bottom2, int bottom3) {
    vtkIdType ptIds[6] = { top1, top2, top3, bottom1, bottom2, bottom3 };
    return gridData_->InsertNextCell(VTK_WEDGE, 6, ptIds);
}

int TriangularPrismVolume::GetPrismCount() const {
    return gridData_->GetNumberOfCells();
}

bool TriangularPrismVolume::GetPrismAt(int i, int& top1, int& top2, int& top3, int& bottom1, int& bottom2, int& bottom3) const {
    vtkIdType npts = 0;
    const vtkIdType* pts = nullptr;
    gridData_->GetCellPoints(i, npts, pts);
    if (npts != 6 || pts == nullptr) {
        return false;
    }
    top1 = pts[0];
    top2 = pts[1];
    top3 = pts[2];
    bottom1 = pts[3];
    bottom2 = pts[4];
    bottom3 = pts[5];
    return true;
}

geo3dml::Box3D TriangularPrismVolume::GetMinimumBoundingRectangle() const {
    geo3dml::Box3D box;
    if (gridData_ != nullptr && gridData_->GetNumberOfPoints() > 0) {
        SetBox3DFromVTKBound(gridData_->GetBounds(), box);
    }
    return box;
}

void TriangularPrismVolume::SetProperty(geo3dml::ShapeProperty* prop, geo3dml::ShapeProperty::SamplingTarget t) {
    shapeHelper_.SetProperty(prop, t, GetID(), gridData_.Get());
}

geo3dml::ShapeProperty* TriangularPrismVolume::TriangularPrismVolume::GetProperty(geo3dml::ShapeProperty::SamplingTarget t) const {
    return shapeHelper_.GetProperty(t, GetID(), gridData_.Get());
}

vtkUnstructuredGrid* TriangularPrismVolume::GetVolumeData() const {
    return gridData_.Get();
}
