#include <g3dvtk/CornerPointGrid.h>
#include <vtkPointData.h>

using namespace g3dvtk;

CornerPointGrid::CornerPointGrid() {

}

CornerPointGrid::CornerPointGrid(int dimI, int dimJ, int dimK) : geo3dml::CornerPointGrid(dimI, dimJ, dimK) {
	Init(dimI, dimJ, dimK);
}

CornerPointGrid::~CornerPointGrid() {

}

bool CornerPointGrid::Init(int dimI, int dimJ, int dimK) {
	if (pillars_ != NULL) {
		return false;
	}
	int numberOfPillars = (dimI + 1) * (dimJ + 1);
	int numberOfPoints = (dimI + 1) * (dimJ + 1) * (dimK + 1);
	pillars_ = vtkSmartPointer<vtkPolyData>::New();
	vtkSmartPointer<vtkPoints> pts = vtkSmartPointer<vtkPoints>::New();
	pts->Allocate(numberOfPillars * 2);
	vtkSmartPointer<vtkCellArray> lines = vtkSmartPointer<vtkCellArray>::New();
	lines->Allocate(numberOfPillars);
	pillars_->SetPoints(pts);
	pillars_->SetLines(lines);
	pts = vtkSmartPointer<vtkPoints>::New();
	pts->Allocate(numberOfPoints);
	cells_ = vtkSmartPointer<vtkStructuredGrid>::New();
	cells_->SetDimensions(dimI + 1, dimJ + 1, dimK + 1);	// vtkStructuredGrid needs to know dimensions in vertices.
	cells_->SetPoints(pts);
	return true;
}

void CornerPointGrid::GetDimensions(int& i, int& j, int& k) {
	g3d_lock_guard lck(mtx_);
	InnerGetDimensions(i, j, k);
}

void CornerPointGrid::InnerGetDimensions(int& i, int& j, int& k) {
	int dims[3] = { 0 };
	cells_->GetCellDims(dims);
	i = dims[0];
	j = dims[1];
	k = dims[2];
}

void CornerPointGrid::AddNextPillar(double headPos[3], double tailPos[3]) {
	g3d_lock_guard lck(mtx_);
	vtkPoints* pts = pillars_->GetPoints();
	vtkIdType headId = pts->InsertNextPoint(headPos);
	vtkIdType tailId = pts->InsertNextPoint(tailPos);
	vtkSmartPointer<vtkIdList> ptList = vtkSmartPointer<vtkIdList>::New();
	ptList->InsertNextId(headId);
	ptList->InsertNextId(tailId);
	pillars_->InsertNextCell(VTK_LINE, ptList);
}

void CornerPointGrid::AddNextCell(
	int i, int j, int k,
	double bottomFrontLeft[3], double bottomFrontRight[3],
	double bottomBackLeft[3], double bottomBackRight[3],
	double topFrontLeft[3], double topFrontRight[3],
	double topBackLeft[3], double topBackRight[3],
	bool beValid
) {
	g3d_lock_guard lck(mtx_);
	int dimI = 0, dimJ = 0, dimK = 0;
	InnerGetDimensions(dimI, dimJ, dimK);
	int numberOfPointsInLayer = (dimJ + 1) * (dimI + 1);
	int numberOfPointsInRow = dimI + 1;
	int baseIndex = k * numberOfPointsInLayer + j * numberOfPointsInRow + i;
	int indexOfBottomFrontLeft = baseIndex;
	int indexOfBottomFrontRight = indexOfBottomFrontLeft + 1;
	int indexOfBottomBackLeft = indexOfBottomFrontLeft + numberOfPointsInRow;
	int indexOfBottomBackRight = indexOfBottomBackLeft + 1;
	int indexOfTopFrontLeft = indexOfBottomFrontLeft + numberOfPointsInLayer;
	int indexOfTopFrontRight = indexOfBottomFrontRight + numberOfPointsInLayer;
	int indexOfTopBackLeft = indexOfBottomBackLeft + numberOfPointsInLayer;
	int indexOfTopBackRight = indexOfBottomBackRight + numberOfPointsInLayer;
	vtkPoints* pts = cells_->GetPoints();
	if (k == 0) {
		// Add points from the bottom face.
		{
			if (j == 0) {
				// Add ponts from the bottom-front face.
				{
					if (i == 0) {
						// Add point at the bottom-front-left position.
						pts->InsertPoint(indexOfBottomFrontLeft, bottomFrontLeft);
					}
					// Add point at the bottom-front-right position.
					pts->InsertPoint(indexOfBottomFrontRight, bottomFrontRight);
				}
			}
			// Add points from the bottom-back face.
			{
				if (i == 0) {
					// Add point at the bottom-back-left position.
					pts->InsertPoint(indexOfBottomBackLeft, bottomBackLeft);
				}
				// Add point at the bottom-back-right position.
				pts->InsertPoint(indexOfBottomBackRight, bottomBackRight);
			}
		}
	}
	// Add points from the top face.
	{
		if (j == 0) {
			// Add points from the top-front face.
			{
				if (i == 0) {
					// Add point at the top-front-left position.
					pts->InsertPoint(indexOfTopFrontLeft, topFrontLeft);
				}
				// Add point at the top-front-right position.
				pts->InsertPoint(indexOfTopFrontRight, topFrontRight);
			}
		}
		// Add points from the top-back face.
		{
			if (i == 0) {
				// Add point at the top-back-left position.
				pts->InsertPoint(indexOfTopBackLeft, topBackLeft);
			}
			// Add point at the top-back-right position.
			pts->InsertPoint(indexOfTopBackRight, topBackRight);
		}
	}
	// validation
	InnerSetCellValidation(i, j, k, beValid);
}

void CornerPointGrid::SetCellValidation(int i, int j, int k, bool isValid) {
	g3d_lock_guard lck(mtx_);
	InnerSetCellValidation(i, j, k, isValid);
	cells_->Modified();
}

void CornerPointGrid::InnerSetCellValidation(int i, int j, int k, bool isValid) {
	int dimI = 0, dimJ = 0, dimK = 0;
	InnerGetDimensions(dimI, dimJ, dimK);
	if (isValid) {
		cells_->UnBlankCell(k * dimJ * dimI + j * dimI + i);
	} else {
		cells_->BlankCell(k* dimJ * dimI + j * dimI + i);
	}
}

void CornerPointGrid::GetCellAt(int i, int j, int k,
	double bottomFrontLeft[3], double bottomFrontRight[3],
	double bottomBackLeft[3], double bottomBackRight[3],
	double topFrontLeft[3], double topFrontRight[3],
	double topBackLeft[3], double topBackRight[3],
	bool& isValid) {
	g3d_lock_guard lck(mtx_);
	int dimI = 0, dimJ = 0, dimK = 0;
	InnerGetDimensions(dimI, dimJ, dimK);
	int numberOfPointsInLayer = (dimJ + 1) * (dimI + 1);
	int numberOfPointsInRow = dimI + 1;
	int baseIndex = k * numberOfPointsInLayer + j * numberOfPointsInRow + i;
	// vertices
	int indexOfBottomFrontLeft = baseIndex;
	int indexOfBottomFrontRight = indexOfBottomFrontLeft + 1;
	int indexOfBottomBackLeft = indexOfBottomFrontLeft + numberOfPointsInRow;
	int indexOfBottomBackRight = indexOfBottomBackLeft + 1;
	int indexOfTopFrontLeft = indexOfBottomFrontLeft + numberOfPointsInLayer;
	int indexOfTopFrontRight = indexOfBottomFrontRight + numberOfPointsInLayer;
	int indexOfTopBackLeft = indexOfBottomBackLeft + numberOfPointsInLayer;
	int indexOfTopBackRight = indexOfBottomBackRight + numberOfPointsInLayer;
	vtkPoints* pts = cells_->GetPoints();
	pts->GetPoint(indexOfBottomFrontLeft, bottomFrontLeft);
	pts->GetPoint(indexOfBottomFrontRight, bottomFrontRight);
	pts->GetPoint(indexOfBottomBackLeft, bottomBackLeft);
	pts->GetPoint(indexOfBottomBackRight, bottomBackRight);
	pts->GetPoint(indexOfTopFrontLeft, topFrontLeft);
	pts->GetPoint(indexOfTopFrontRight, topFrontRight);
	pts->GetPoint(indexOfTopBackLeft, topBackLeft);
	pts->GetPoint(indexOfTopBackRight, topBackRight);
	// validation
	isValid = cells_->IsCellVisible(k * dimJ * dimI + j * dimI + i);
}

void CornerPointGrid::GetPillarAt(int i, int j, double headPos[3], double tailPos[3]) {
	g3d_lock_guard lck(mtx_);
	int dimI = 0, dimJ = 0, dimK = 0;
	InnerGetDimensions(dimI, dimJ, dimK);
	int index = j * (dimI + 1) + i;
	vtkCell* cell = pillars_->GetCell(index);
	vtkIdType pt0 = cell->GetPointId(0);
	vtkIdType pt1 = cell->GetPointId(1);
	pillars_->GetPoint(pt0, headPos);
	pillars_->GetPoint(pt1, tailPos);
}

vtkPolyData* CornerPointGrid::GetPillars() {
	g3d_lock_guard lck(mtx_);
	return pillars_;
}

vtkStructuredGrid* CornerPointGrid::GetStructuredGrid() {
	g3d_lock_guard lck(mtx_);
	return cells_;
}

void CornerPointGrid::SetProperty(geo3dml::ShapeProperty* prop, geo3dml::ShapeProperty::SamplingTarget t) {
	g3d_lock_guard lck(mtx_);
	shapeHelper_.SetProperty(prop, t, GetID(), cells_);
}

geo3dml::ShapeProperty* CornerPointGrid::GetProperty(geo3dml::ShapeProperty::SamplingTarget t) {
	g3d_lock_guard lck(mtx_);
	return shapeHelper_.GetProperty(t, GetID(), cells_);
}

bool CornerPointGrid::GetMinimumBoundingRectangle(double& minX, double& minY, double& minZ, double& maxX, double& maxY, double& maxZ) {
	g3d_lock_guard lck(mtx_);
	if (cells_ == NULL || cells_->GetNumberOfPoints() < 1) {
		return false;
	}
	double bounds[6] = {0};
	cells_->GetBounds(bounds);
	minX = bounds[0];
	maxX = bounds[1];
	minY = bounds[2];
	maxY = bounds[3];
	minZ = bounds[4];
	maxZ = bounds[5];
	return true;
}
