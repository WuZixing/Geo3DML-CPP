#include <g3dvtk/MultiLineString.h>
#include <vtkPolyLine.h>
#include "Utils.h"

using namespace g3dvtk;


MultiLineString::MultiLineString() {
	polyData_ = vtkSmartPointer<vtkPolyData>::New();
	vtkSmartPointer<vtkPoints> pts = vtkSmartPointer<vtkPoints>::New();
    pts->SetDataTypeToDouble();
	vtkSmartPointer<vtkCellArray> lines = vtkSmartPointer<vtkCellArray>::New();
	polyData_->SetPoints(pts);
	polyData_->SetLines(lines);
}

MultiLineString::~MultiLineString() {

}


int MultiLineString::AddLineString(const geo3dml::LineString* line) {
	vtkSmartPointer<vtkIdList> ptList = vtkSmartPointer<vtkIdList>::New();
	double x = 0, y = 0, z = 0;
	for (int n = 0; n < line->GetVertexCount(); ++n) {
		line->GetVertexAt(n, x, y, z);
		vtkIdType ptIndex = polyData_->GetPoints()->InsertNextPoint(x, y, z);
		ptList->InsertNextId(ptIndex);
	}
	int lineIndex = polyData_->GetLines()->InsertNextCell(ptList);
	polyData_->Modified();
	return lineIndex;
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
	const vtkIdType* pts = nullptr;
	lineArray->GetCellAtId(lineIndex, cellSize, pts);
	if (vertexIndex >= 0 && vertexIndex < cellSize) {
		vtkIdType ptIndex = pts[vertexIndex];
		double coords[3];
		polyData_->GetPoints()->GetPoint(ptIndex, coords);
		x = coords[0];
		y = coords[1];
		z = coords[2];
	}
}

geo3dml::Box3D MultiLineString::GetMinimumBoundingRectangle() const {
	geo3dml::Box3D box;
	if (polyData_ != nullptr && polyData_->GetNumberOfPoints() > 0) {
		SetBox3DFromVTKBound(polyData_->GetBounds(), box);
	}
	return box;
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
