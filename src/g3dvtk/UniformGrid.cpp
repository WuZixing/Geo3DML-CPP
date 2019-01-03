#include <g3dvtk/UniformGrid.h>

using namespace g3dvtk;

UniformGrid::UniformGrid() {

}

UniformGrid::UniformGrid(double originX, double originY, double originZ, double stepX, double stepY, double stepZ, int dimI, int dimJ, int dimK) : geo3dml::UniformGrid(originX, originY, originZ, stepX, stepY, stepZ, dimI, dimJ, dimK) {
	Init(originX, originY, originZ, stepX, stepY, stepZ, dimI, dimJ, dimK);
}

UniformGrid::~UniformGrid() {

}

bool UniformGrid::Init(double originX, double originY, double originZ,
	double stepX, double stepY, double stepZ,
	int dimI, int dimJ, int dimK) {
	if (uniformGrid_ != NULL) {
		return false;
	}
	uniformGrid_ = vtkSmartPointer<vtkUniformGrid>::New();
	uniformGrid_->SetDimensions(dimI + 1, dimJ + 1, dimK + 1);	// vtkImageData needs to know dimensions in points.
	uniformGrid_->SetOrigin(originX, originY, originZ);
	uniformGrid_->SetSpacing(stepX, stepY, stepZ);
	return true;
}

void UniformGrid::GetDimensions(int& i, int& j, int& k) {
	g3d_lock_guard lck(mtx_);
	int dims[3] = {0};
	uniformGrid_->GetDimensions(dims);
	i = dims[0] - 1;
	j = dims[1] - 1;
	k = dims[2] - 1;
}

void UniformGrid::SetCellValidation(int i, int j, int k, bool beValid) {
	g3d_lock_guard lck(mtx_);
	int dimI = 0, dimJ = 0, dimK = 0;
	GetDimensions(dimI, dimJ, dimK);
	int cellId = k * dimJ * dimI + j * dimI + i;
	if (beValid) {
		uniformGrid_->UnBlankCell(cellId);
	} else {
		uniformGrid_->BlankCell(cellId);
	}
	uniformGrid_->Modified();
}

bool UniformGrid::IsCellValid(int i, int j, int k) {
	g3d_lock_guard lck(mtx_);
	int dimI = 0, dimJ = 0, dimK = 0;
	GetDimensions(dimI, dimJ, dimK);
	int cellId = k * dimJ * dimI + j * dimI + i;
	return uniformGrid_->IsCellVisible(cellId);
}

void UniformGrid::GetOrigin(double& x, double& y, double& z) {
	g3d_lock_guard lck(mtx_);
	uniformGrid_->GetOrigin(x, y, z);
}

void UniformGrid::GetSteps(double& sx, double& sy, double& sz) {
	g3d_lock_guard lck(mtx_);
	uniformGrid_->GetSpacing(sx, sy, sz);
}

vtkUniformGrid* UniformGrid::GetUniformGrid() {
	g3d_lock_guard lck(mtx_);
	return uniformGrid_;
}

void UniformGrid::SetProperty(geo3dml::ShapeProperty* prop, geo3dml::ShapeProperty::SamplingTarget t) {
	g3d_lock_guard lck(mtx_);
	shapeHelper_.SetProperty(prop, t, GetID(), uniformGrid_);
}

geo3dml::ShapeProperty* UniformGrid::GetProperty(geo3dml::ShapeProperty::SamplingTarget t) {
	g3d_lock_guard lck(mtx_);
	return shapeHelper_.GetProperty(t, GetID(), uniformGrid_);
}

bool UniformGrid::GetMinimumBoundingRectangle(double& minX, double& minY, double& minZ, double& maxX, double& maxY, double& maxZ) {
	g3d_lock_guard lck(mtx_);
	if (uniformGrid_ == NULL || uniformGrid_->GetNumberOfPoints() < 1) {
		return false;
	}
	double bounds[6] = { 0 };
	uniformGrid_->GetBounds(bounds);
	minX = bounds[0];
	maxX = bounds[1];
	minY = bounds[2];
	maxY = bounds[3];
	minZ = bounds[4];
	maxZ = bounds[5];
	return true;
}

int UniformGrid::CalculateCellIndex(int i, int j, int k) {
	g3d_lock_guard lck(mtx_);
	int dimI = 0, dimJ = 0, dimK = 0;
	GetDimensions(dimI, dimJ, dimK);
	return  k * dimJ * dimI + j * dimI + i;
}
