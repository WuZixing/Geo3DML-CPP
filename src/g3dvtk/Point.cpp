#include <g3dvtk/Point.h>
#include "Utils.h"

using namespace g3dvtk;

Point::Point() {
	polyData_ = vtkSmartPointer<vtkPolyData>::New();
	vtkSmartPointer<vtkPoints> pts = vtkSmartPointer<vtkPoints>::New();
    pts->SetDataTypeToDouble();
	vtkSmartPointer<vtkCellArray> verts = vtkSmartPointer<vtkCellArray>::New();
	polyData_->SetPoints(pts);
	polyData_->SetVerts(verts);
}

Point::~Point() {

}

void Point::SetPosition(double x, double y, double z) {
	vtkPoints* pts = polyData_->GetPoints();
	if (pts->GetNumberOfPoints() > 0) {
		pts->SetPoint(0, x, y, z);
	} else {
		vtkIdType ptIndex = pts->InsertNextPoint(x, y, z);
		polyData_->InsertNextCell(VTK_VERTEX, 1, &ptIndex);
	}
	polyData_->Modified();
}

void Point::GetPosition(double& x, double& y, double& z) const {
	vtkPoints* pts = polyData_->GetPoints();
	if (pts->GetNumberOfPoints() > 0) {
		double coords[3] = {0.0};
		pts->GetPoint(0, coords);
		x = coords[0];
		y = coords[1];
		z = coords[2];
	} else {
		x = y = z = 0;
	}
}

double Point::GetX() const {
	vtkPoints* pts = polyData_->GetPoints();
	if (pts->GetNumberOfPoints() > 0) {
		const double* buf = pts->GetPoint(0);
		return buf[0];
	} else {
		return 0;
	}
}
double Point::GetY() const {
	vtkPoints* pts = polyData_->GetPoints();
	if (pts->GetNumberOfPoints() > 0) {
		const double* buf = pts->GetPoint(0);
		return buf[1];
	} else {
		return 0;
	}
}

double Point::GetZ() const {
	vtkPoints* pts = polyData_->GetPoints();
	if (pts->GetNumberOfPoints() > 0) {
		const double* buf = pts->GetPoint(0);
		return buf[2];
	} else {
		return 0;
	}
}

void Point::SetProperty(geo3dml::ShapeProperty* prop, geo3dml::ShapeProperty::SamplingTarget t) {
	shapeHelper_.SetProperty(prop, t, GetID(), polyData_);
}

geo3dml::ShapeProperty* Point::GetProperty(geo3dml::ShapeProperty::SamplingTarget t) const {
	return shapeHelper_.GetProperty(t, GetID(), polyData_);
}

vtkPolyData* Point::GetPolyData() const {
	if (polyData_ != NULL && polyData_->NeedToBuildCells()) {
		polyData_->BuildCells();
	}
	return polyData_;
}

geo3dml::Box3D Point::GetMinimumBoundingRectangle() const {
	geo3dml::Box3D box;
	if (polyData_ != nullptr && polyData_->GetNumberOfPoints() > 0) {
		SetBox3DFromVTKBound(polyData_->GetBounds(), box);
	}
	return box;
}
