#include <g3dvtk/TIN.h>
#include <vtkCellArray.h>
#include "Utils.h"

using namespace g3dvtk;

TIN::TIN() {
	polyData_ = vtkSmartPointer<vtkPolyData>::New();
	vtkSmartPointer<vtkPoints> pts = vtkSmartPointer<vtkPoints>::New();
    pts->SetDataTypeToDouble();
	vtkSmartPointer<vtkCellArray> polys = vtkSmartPointer<vtkCellArray>::New();
	polyData_->SetPoints(pts);
	polyData_->SetPolys(polys);
}

TIN::~TIN() {

}

void TIN::AppendVertex(double x, double y, double z) {
	vtkPoints* pts = polyData_->GetPoints();
	pts->InsertNextPoint(x, y, z);
}

int TIN::GetVertexCount() const {
	return polyData_->GetNumberOfPoints();
}

void TIN::GetVertexAt(int i, double& x, double& y, double& z) const {
	vtkPoints* pts = polyData_->GetPoints();
	double coords[3];
	pts->GetPoint(i, coords);
	x = coords[0];
	y = coords[1];
	z = coords[2];
}

void TIN::AppendTriangle(int v1, int v2, int v3) {
	vtkIdType vertices[3] = {v1, v2, v3};
	polyData_->InsertNextCell(VTK_TRIANGLE, 3, vertices);
}

int TIN::GetTriangleCount() const {
	return polyData_->GetNumberOfPolys();
}

void TIN::GetTriangleAt(int i, int& vertex1, int& vertex2, int& vertex3) const {
	vtkIdType npts = 0;
	const vtkIdType* pts = NULL;
	polyData_->GetCellPoints(i, npts, pts);
	vertex1 = pts[0];
	vertex2 = pts[1];
	vertex3 = pts[2];
}

vtkPolyData* TIN::GetPolyData() const {
	if (polyData_ != NULL && polyData_->NeedToBuildCells()) {
		polyData_->BuildCells();
	}
	return polyData_;
}

void TIN::SetProperty(geo3dml::ShapeProperty* prop, geo3dml::ShapeProperty::SamplingTarget t) {
	shapeHelper_.SetProperty(prop, t, GetID(), polyData_);
}

geo3dml::ShapeProperty* TIN::GetProperty(geo3dml::ShapeProperty::SamplingTarget t) const {
	return shapeHelper_.GetProperty(t, GetID(), polyData_);
}

geo3dml::Box3D TIN::GetMinimumBoundingRectangle() const {
	geo3dml::Box3D box;
	if (polyData_ != nullptr && polyData_->GetNumberOfPoints() > 0) {
		SetBox3DFromVTKBound(polyData_->GetBounds(), box);
	}
	return box;
}
