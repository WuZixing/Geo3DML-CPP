// UTF-8编码
#include <g3dvtk/GTPVolume.h>
#include <vtkCellArray.h>

using namespace g3dvtk;

GTPVolume::GTPVolume() {
	gridData_ = vtkSmartPointer<vtkUnstructuredGrid>::New();
	vtkSmartPointer<vtkPoints> pts = vtkSmartPointer<vtkPoints>::New();
	gridData_->SetPoints(pts);
}

GTPVolume::~GTPVolume() {

}

int GTPVolume::AppendVertex(double x, double y, double z) {
	vtkPoints* pts = gridData_->GetPoints();
	return pts->InsertNextPoint(x, y, z);
}

int GTPVolume::GetVertexCount() const {
	return gridData_->GetNumberOfPoints();
}

bool GTPVolume::GetVertexAt(int i, double& x, double& y, double& z) const {
	vtkPoints* pts = gridData_->GetPoints();
	double coords[3];
	pts->GetPoint(i, coords);
	x = coords[0];
	y = coords[1];
	z = coords[2];
	return true;
}

int GTPVolume::AppendPrism(int topVertex1, int topVertex2, int topVertex3, int bottomVertex1, int bottomVertex2, int bottomVertex3) {
	vtkIdType ptIds[6] = {topVertex1, topVertex2, topVertex3, bottomVertex1, bottomVertex2, bottomVertex3};
	vtkNew<vtkIdList> faces;
	// 顶面
	faces->InsertNextId(3);
	faces->InsertNextId(topVertex1);
	faces->InsertNextId(topVertex2);
	faces->InsertNextId(topVertex3);
	// 底面
	faces->InsertNextId(3);
	faces->InsertNextId(bottomVertex1);
	faces->InsertNextId(bottomVertex2);
	faces->InsertNextId(bottomVertex3);
	// 侧面：1
	faces->InsertNextId(4);
	faces->InsertNextId(topVertex1);
	faces->InsertNextId(topVertex2);
	faces->InsertNextId(bottomVertex2);
	faces->InsertNextId(bottomVertex1);
	// 侧面：2
	faces->InsertNextId(4);
	faces->InsertNextId(topVertex2);
	faces->InsertNextId(topVertex3);
	faces->InsertNextId(bottomVertex3);
	faces->InsertNextId(bottomVertex2);
	// 侧面：3
	faces->InsertNextId(4);
	faces->InsertNextId(topVertex3);
	faces->InsertNextId(topVertex1);
	faces->InsertNextId(bottomVertex1);
	faces->InsertNextId(bottomVertex3);

	return gridData_->InsertNextCell(VTK_POLYHEDRON, 6, ptIds, 5, faces->GetPointer(0));
}

int GTPVolume::GetPrismCount() const {
	return gridData_->GetNumberOfCells();
}

bool GTPVolume::GetPrismAt(int i, int& topVertex1, int& topVertex2, int topVertex3, int bottomVertex1, int& bottomVertex2, int& bottomVertex3) const {
	vtkIdType npts = 0;
	const vtkIdType* pts = nullptr;
	gridData_->GetCellPoints(i, npts, pts);
	if (npts != 6 || pts == nullptr) {
		return false;
	}
	topVertex1 = pts[0];
	topVertex2 = pts[1];
	topVertex3 = pts[2];
	bottomVertex1 = pts[3];
	bottomVertex2 = pts[4];
	bottomVertex3 = pts[5];
	return true;
}

bool GTPVolume::GetMinimumBoundingRectangle(double& minX, double& minY, double& minZ, double& maxX, double& maxY, double& maxZ) const {
	if (gridData_ == NULL || gridData_->GetNumberOfPoints() < 1) {
		return false;
	}
	double bounds[6] = { 0 };
	gridData_->GetBounds(bounds);
	minX = bounds[0];
	maxX = bounds[1];
	minY = bounds[2];
	maxY = bounds[3];
	minZ = bounds[4];
	maxZ = bounds[5];
	return true;
}

void GTPVolume::SetProperty(geo3dml::ShapeProperty* prop, geo3dml::ShapeProperty::SamplingTarget t) {
	shapeHelper_.SetProperty(prop, t, GetID(), gridData_.Get());
}

geo3dml::ShapeProperty* GTPVolume::GTPVolume::GetProperty(geo3dml::ShapeProperty::SamplingTarget t) const {
	return shapeHelper_.GetProperty(t, GetID(), gridData_.Get());
}

vtkUnstructuredGrid* GTPVolume::GetVolumeData() const {
	return gridData_.Get();
}
