#include <g3dvtk/LineString.h>

using namespace g3dvtk;

LineString::LineString() {
	polyData_ = vtkSmartPointer<vtkPolyData>::New();
	vtkSmartPointer<vtkPoints> pts = vtkSmartPointer<vtkPoints>::New();
	vtkSmartPointer<vtkCellArray> lines = vtkSmartPointer<vtkCellArray>::New();
	polyData_->SetPoints(pts);
	polyData_->SetLines(lines);
}

LineString::~LineString() {

}

void LineString::AddVertex(double x, double y, double z) {
	g3d_lock_guard lck(mtx_);
	vtkPoints* pts = polyData_->GetPoints();
	vtkIdType lastPt = pts->InsertNextPoint(x, y, z);
	if (pts->GetNumberOfPoints() > 1) {
		vtkIdType previousPt = lastPt - 1;
		vtkSmartPointer<vtkIdList> ptList = vtkSmartPointer<vtkIdList>::New();
		ptList->Allocate(2);
		ptList->InsertNextId(previousPt);
		ptList->InsertNextId(lastPt);
		polyData_->InsertNextCell(VTK_LINE, ptList);
	}
}

int LineString::GetVertexCount() {
	g3d_lock_guard lck(mtx_);
	return polyData_->GetNumberOfPoints();
}

void LineString::GetVertexAt(int i, double& x, double& y, double& z) {
	g3d_lock_guard lck(mtx_);
	vtkPoints* pts = polyData_->GetPoints();
	double coords[3] = {0.0};
	pts->GetPoint(i, coords);
	x = coords[0];
	y = coords[1];
	z = coords[2];
}

vtkPolyData* LineString::GetPolyData() {
	g3d_lock_guard lck(mtx_);
	return polyData_;
}

void LineString::SetProperty(geo3dml::ShapeProperty* prop, geo3dml::ShapeProperty::SamplingTarget t) {
	g3d_lock_guard lck(mtx_);
	shapeHelper_.SetProperty(prop, t, GetID(), polyData_);
}

geo3dml::ShapeProperty* LineString::GetProperty(geo3dml::ShapeProperty::SamplingTarget t) {
	g3d_lock_guard lck(mtx_);
	return shapeHelper_.GetProperty(t, GetID(), polyData_);
}

bool LineString::GetMinimumBoundingRectangle(double& minX, double& minY, double& minZ, double& maxX, double& maxY, double& maxZ) {
	g3d_lock_guard lck(mtx_);
	if (polyData_ == NULL || polyData_->GetNumberOfPoints() < 1) {
		return false;
	}
	double bounds[6] = {0};
	polyData_->GetBounds(bounds);
	minX = bounds[0];
	maxX = bounds[1];
	minY = bounds[2];
	maxY = bounds[3];
	minZ = bounds[4];
	maxZ = bounds[5];
	return true;
}
