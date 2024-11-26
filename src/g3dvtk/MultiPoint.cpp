#include <g3dvtk/MultiPoint.h>
#include "Utils.h"

using namespace g3dvtk;

MultiPoint::MultiPoint() {
	polyData_ = vtkSmartPointer<vtkPolyData>::New();
	vtkSmartPointer<vtkPoints> pts = vtkSmartPointer<vtkPoints>::New();
    pts->SetDataTypeToDouble();
	vtkSmartPointer<vtkCellArray> verts = vtkSmartPointer<vtkCellArray>::New();
	polyData_->SetPoints(pts);
	polyData_->SetVerts(verts);
}

MultiPoint::~MultiPoint() {

}

void MultiPoint::AddPoint(double x, double y, double z) {
	vtkIdType ptIndex = polyData_->GetPoints()->InsertNextPoint(x, y, z);
	polyData_->InsertNextCell(VTK_VERTEX, 1, &ptIndex);
	polyData_->Modified();
}

int MultiPoint::GetPointCount() const {
	return polyData_->GetNumberOfPoints();
}

void MultiPoint::GetPointAt(int i, double& x, double& y, double& z) const {
	double coords[3] = {0.0};
	polyData_->GetPoints()->GetPoint(i, coords);
	x = coords[0];
	y = coords[1];
	z = coords[2];
}

geo3dml::Box3D MultiPoint::GetMinimumBoundingRectangle() const {
	geo3dml::Box3D box;
	if (polyData_ != nullptr && polyData_->GetNumberOfPoints() > 0) {
		SetBox3DFromVTKBound(polyData_->GetBounds(), box);
	}
	return box;
}

void MultiPoint::SetProperty(geo3dml::ShapeProperty* prop, geo3dml::ShapeProperty::SamplingTarget t) {
	shapeHelper_.SetProperty(prop, t, GetID(), polyData_);
}

geo3dml::ShapeProperty* MultiPoint::GetProperty(geo3dml::ShapeProperty::SamplingTarget t) const {
	return shapeHelper_.GetProperty(t, GetID(), polyData_);
}

vtkPolyData* MultiPoint::GetPolyData() const {
	if (polyData_ != NULL && polyData_->NeedToBuildCells()) {
		polyData_->BuildCells();
	}
	return polyData_;
}
