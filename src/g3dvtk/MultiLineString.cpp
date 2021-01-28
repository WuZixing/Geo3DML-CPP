#include <g3dvtk/MultiLineString.h>
#include <vtkPolyLine.h>

using namespace g3dvtk;


MultiLineString::MultiLineString() {
	polyData_ = vtkSmartPointer<vtkPolyData>::New();
	vtkSmartPointer<vtkPoints> pts = vtkSmartPointer<vtkPoints>::New();
	vtkSmartPointer<vtkCellArray> lines = vtkSmartPointer<vtkCellArray>::New();
	polyData_->SetPoints(pts);
	polyData_->SetLines(lines);
}

MultiLineString::~MultiLineString() {

}


int MultiLineString::AddLineString() {
	vtkSmartPointer<vtkPolyLine> polyLine = vtkSmartPointer<vtkPolyLine>::New();
	return polyData_->GetLines()->InsertNextCell(polyLine);
}

void MultiLineString::AddVertexToLineString(int lineIndex, double x, double y, double z) {
	vtkCellArray* lineArray = polyData_->GetLines();
	if (lineIndex < 0 || lineIndex >= lineArray->GetNumberOfCells()) {
		return;
	}
	vtkIdType ptIndex = polyData_->GetPoints()->InsertNextPoint(x, y, z);
	vtkSmartPointer<vtkIdList> ptList = vtkSmartPointer<vtkIdList>::New();
	lineArray->GetCell(lineIndex, ptList);
	ptList->InsertNextId(ptIndex);
	lineArray->ReplaceCell(lineIndex, ptList->GetNumberOfIds(), ptList->begin());
	polyData_->Modified();
}

int MultiLineString::GetVertexCountOfLineString(int lineIndex) const {
	vtkCellArray* lineArray = polyData_->GetLines();
	if (lineIndex >= 0 && lineIndex < lineArray->GetNumberOfCells()) {
		return lineArray->GetCellSize(lineIndex);
	} else {
		return 0;
	}

}

int MultiLineString::GetLineStringCount() const {
	return polyData_->GetNumberOfLines();
}

void MultiLineString::GetVertexOfLineString(int lineIndex, int vertexIndex, double& x, double& y, double& z) const {
	vtkCellArray* lineArray = polyData_->GetLines();
	if (lineIndex < 0 || lineIndex >= lineArray->GetNumberOfCells()) {
		return;
	}
	vtkIdType cellSize = 0;
	const vtkIdType* idList = NULL;
	lineArray->GetCell(lineIndex, cellSize, idList);
	if (vertexIndex >= 0 && vertexIndex < cellSize) {
		vtkIdType ptIndex = idList[vertexIndex];
		double coords[3];
		polyData_->GetPoints()->GetPoint(ptIndex, coords);
		x = coords[0];
		y = coords[1];
		z = coords[2];
	}
}

bool MultiLineString::GetMinimumBoundingRectangle(double& minX, double& minY, double& minZ, double& maxX, double& maxY, double& maxZ) const {
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

void MultiLineString::SetProperty(geo3dml::ShapeProperty* prop, geo3dml::ShapeProperty::SamplingTarget t) {
	shapeHelper_.SetProperty(prop, t, GetID(), polyData_);
}

geo3dml::ShapeProperty* MultiLineString::GetProperty(geo3dml::ShapeProperty::SamplingTarget t) const {
	return shapeHelper_.GetProperty(t, GetID(), polyData_);
}

vtkPolyData* MultiLineString::GetPolyData() const {
	if (polyData_ != NULL && polyData_->NeedToBuildCells()) {
		polyData_->BuildCells();
	}
	return polyData_;
}
