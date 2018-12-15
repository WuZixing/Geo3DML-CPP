#include <g3dvtk/MultiPoint.h>

using namespace g3dvtk;

MultiPoint::MultiPoint() {
	polyData_ = vtkSmartPointer<vtkPolyData>::New();
	vtkSmartPointer<vtkPoints> pts = vtkSmartPointer<vtkPoints>::New();
	vtkSmartPointer<vtkCellArray> verts = vtkSmartPointer<vtkCellArray>::New();
	polyData_->SetPoints(pts);
	polyData_->SetVerts(verts);
}

MultiPoint::~MultiPoint() {

}

void MultiPoint::AddPoint(double x, double y, double z) {
	g3d_lock_guard lck(mtx_);
	vtkIdType ptIndex = polyData_->GetPoints()->InsertNextPoint(x, y, z);
	polyData_->InsertNextCell(VTK_VERTEX, 1, &ptIndex);
	polyData_->Modified();
}

int MultiPoint::GetPointCount() {
	g3d_lock_guard lck(mtx_);
	return polyData_->GetNumberOfPoints();
}

void MultiPoint::GetPointAt(int i, double& x, double& y, double& z) {
	g3d_lock_guard lck(mtx_);
	double coords[3] = {0.0};
	polyData_->GetPoints()->GetPoint(i, coords);
	x = coords[0];
	y = coords[1];
	z = coords[2];
}

bool MultiPoint::GetMinimumBoundingRectangle(double& minX, double& minY, double& minZ, double& maxX, double& maxY, double& maxZ) {
	g3d_lock_guard lck(mtx_);
	if (polyData_ == NULL || polyData_->GetNumberOfPoints() < 1) {
		return false;
	}
	double bounds[6] = { 0 };
	polyData_->GetBounds(bounds);
	minX = bounds[0];
	maxX = bounds[1];
	minY = bounds[2];
	maxY = bounds[3];
	minZ = bounds[4];
	maxZ = bounds[5];
	return true;
}

void MultiPoint::SetProperty(geo3dml::ShapeProperty* prop, geo3dml::ShapeProperty::SamplingTarget t) {
	g3d_lock_guard lck(mtx_);
	shapeHelper_.SetProperty(prop, t, GetID(), polyData_);
}

geo3dml::ShapeProperty* MultiPoint::GetProperty(geo3dml::ShapeProperty::SamplingTarget t) {
	g3d_lock_guard lck(mtx_);
	return shapeHelper_.GetProperty(t, GetID(), polyData_);
}

vtkPolyData* MultiPoint::GetPolyData() {
	g3d_lock_guard lck(mtx_);
	return polyData_;
}
