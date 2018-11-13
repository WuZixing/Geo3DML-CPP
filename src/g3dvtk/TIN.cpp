#include <g3dvtk/TIN.h>

using namespace g3dvtk;

TIN::TIN() {
	polyData_ = vtkSmartPointer<vtkPolyData>::New();
	vtkSmartPointer<vtkPoints> pts = vtkSmartPointer<vtkPoints>::New();
	vtkSmartPointer<vtkCellArray> polys = vtkSmartPointer<vtkCellArray>::New();
	polyData_->SetPoints(pts);
	polyData_->SetPolys(polys);
}

TIN::~TIN() {

}

void TIN::AddVertex(int index, double x, double y, double z) {
	g3d_lock_guard lck(mtx_);
	vtkPoints* pts = polyData_->GetPoints();
	pts->InsertPoint(index, x, y, z);
}

int TIN::GetVertexCount() {
	g3d_lock_guard lck(mtx_);
	return polyData_->GetNumberOfPoints();
}

void TIN::GetVertexAt(int i, double& x, double& y, double& z) {
	g3d_lock_guard lck(mtx_);
	vtkPoints* pts = polyData_->GetPoints();
	double coords[3];
	pts->GetPoint(i, coords);
	x = coords[0];
	y = coords[1];
	z = coords[2];
}

void TIN::AddTriangle(int index, int vertex1, int vertex2, int vertex3) {
	g3d_lock_guard lck(mtx_);
	if (vertex1 < 0 || vertex2 < 0 || vertex3 < 0) {
		// invalid vertex index.
		return;
	}
	vtkPoints* pts = polyData_->GetPoints();
	vtkIdType ptNum = pts->GetNumberOfPoints();
	if (vertex1 >= ptNum || vertex2 >= ptNum || vertex3 >= ptNum) {
		// invalid vertex index.
		return;
	}
	vtkSmartPointer<vtkIdList> ptList = vtkSmartPointer<vtkIdList>::New();
	ptList->Allocate(3);
	ptList->InsertNextId(vertex1);
	ptList->InsertNextId(vertex2);
	ptList->InsertNextId(vertex3);
	polyData_->InsertNextCell(VTK_TRIANGLE, ptList);
}

int TIN::GetTriangleCount() {
	g3d_lock_guard lck(mtx_);
	return polyData_->GetNumberOfPolys();
}

void TIN::GetTriangleAt(int i, int& vertex1, int& vertex2, int& vertex3) {
	g3d_lock_guard lck(mtx_);
	vtkSmartPointer<vtkIdList> ptList = vtkSmartPointer<vtkIdList>::New();
	polyData_->GetCellPoints(i, ptList);
	if (ptList->GetNumberOfIds() == 3) {
		vertex1 = ptList->GetId(0);
		vertex2 = ptList->GetId(1);
		vertex3 = ptList->GetId(2);
	}
}

vtkPolyData* TIN::GetPolyData() {
	g3d_lock_guard lck(mtx_);
	return polyData_;
}

void TIN::SetProperty(geo3dml::ShapeProperty* prop, geo3dml::ShapeProperty::SamplingTarget t) {
	g3d_lock_guard lck(mtx_);
	shapeHelper_.SetProperty(prop, t, GetID(), polyData_);
}

geo3dml::ShapeProperty* TIN::GetProperty(geo3dml::ShapeProperty::SamplingTarget t) {
	g3d_lock_guard lck(mtx_);
	return shapeHelper_.GetProperty(t, GetID(), polyData_);
}

void TIN::GetBoundingBox(double& minX, double& minY, double& minZ, double& maxX, double& maxY, double& maxZ) {
	g3d_lock_guard lck(mtx_);
	double bounds[6] = { 0 };
	polyData_->GetBounds(bounds);
	minX = bounds[0];
	maxX = bounds[1];
	minY = bounds[2];
	maxY = bounds[3];
	minZ = bounds[4];
	maxZ = bounds[5];
}
