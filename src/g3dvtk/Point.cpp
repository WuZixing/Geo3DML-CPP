#include <g3dvtk/Point.h>

using namespace g3dvtk;

Point::Point() {
	polyData_ = vtkSmartPointer<vtkPolyData>::New();
	vtkSmartPointer<vtkPoints> pts = vtkSmartPointer<vtkPoints>::New();
	vtkSmartPointer<vtkCellArray> verts = vtkSmartPointer<vtkCellArray>::New();
	polyData_->SetPoints(pts);
	polyData_->SetVerts(verts);
}

Point::~Point() {

}

void Point::SetPosition(double x, double y, double z) {
	g3d_lock_guard lck(mtx_);
	vtkPoints* pts = polyData_->GetPoints();
	if (pts->GetNumberOfPoints() > 0) {
		pts->SetPoint(0, x, y, z);
	} else {
		vtkIdType ptIndex = pts->InsertNextPoint(x, y, z);
		polyData_->InsertNextCell(VTK_VERTEX, 1, &ptIndex);
	}
}

void Point::GetPosition(double& x, double& y, double& z) {
	g3d_lock_guard lck(mtx_);
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

void Point::SetProperty(geo3dml::ShapeProperty* prop, geo3dml::ShapeProperty::SamplingTarget t) {
	g3d_lock_guard lck(mtx_);
	shapeHelper_.SetProperty(prop, t, GetID(), polyData_);
}

geo3dml::ShapeProperty* Point::GetProperty(geo3dml::ShapeProperty::SamplingTarget t) {
	g3d_lock_guard lck(mtx_);
	return shapeHelper_.GetProperty(t, GetID(), polyData_);
}

vtkPolyData* Point::GetPolyData() {
	g3d_lock_guard lck(mtx_);
	return polyData_;
}
