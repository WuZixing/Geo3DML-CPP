// UTF-8编码
#include <g3dvtk/TruncatedRegularGrid.h>
#include <vtkIdList.h>
#include "Utils.h"

using namespace g3dvtk;

TruncatedRegularGrid::TruncatedRegularGrid() {
    gridData_ = vtkSmartPointer<vtkUnstructuredGrid>::New();
    vtkSmartPointer<vtkPoints> pts = vtkSmartPointer<vtkPoints>::New();
    pts->SetDataTypeToDouble();
    gridData_->SetPoints(pts);
}

TruncatedRegularGrid::~TruncatedRegularGrid() {

}

int TruncatedRegularGrid::AppendVertex(double x, double y, double z) {
    vtkPoints* pts = gridData_->GetPoints();
    return pts->InsertNextPoint(x, y, z);
}

int TruncatedRegularGrid::GetVertexCount() const {
    return gridData_->GetNumberOfPoints();
}

bool TruncatedRegularGrid::GetVertexAt(int i, double& x, double& y, double& z) const {
    vtkPoints* pts = gridData_->GetPoints();
    double coords[3];
    pts->GetPoint(i, coords);
    x = coords[0];
    y = coords[1];
    z = coords[2];
    return true;
}

int TruncatedRegularGrid::AppendFace(const std::list<int>& vertices) {
    Face face;
    face.vertices = vertices;
    faces_.push_back(face);
    return faces_.size() - 1;
}

int TruncatedRegularGrid::GetFaceCount() const {
    return faces_.size();
}

bool TruncatedRegularGrid::GetFaceAt(int i, std::list<int>& vertices) const {
    const Face& face = faces_.at(i);
    vertices = face.vertices;
    return true;
}

int TruncatedRegularGrid::AppendCell(const std::list<int>& faces, int i, int j, int k) {
    vtkNew<vtkIdList> ptIds;
    ptIds->InsertNextId(faces.size());
    for (auto faceItor = faces.cbegin(); faceItor != faces.cend(); ++faceItor) {
        const Face& face = faces_.at(*faceItor);
        ptIds->InsertNextId(face.vertices.size());
        for (auto cItor = face.vertices.cbegin(); cItor != face.vertices.cend(); ++cItor) {
            ptIds->InsertNextId(*cItor);
        }
    }
    Cell cell;
    cell.faces = faces;
    cell.i = i;
    cell.j = j;
    cell.k = k;
    cells_.push_back(cell);
    return gridData_->InsertNextCell(VTK_POLYHEDRON, ptIds);
}

int TruncatedRegularGrid::GetCellCount() const {
    return gridData_->GetNumberOfCells();
}

bool TruncatedRegularGrid::GetCellAt(int n, std::list<int>& faces, int& i, int& j, int& k) const {
    const Cell& cell = cells_.at(n);
    faces = cell.faces;
    i = cell.i;
    j = cell.j;
    k = cell.k;
    return true;
}

geo3dml::Box3D TruncatedRegularGrid::GetMinimumBoundingRectangle() const {
    geo3dml::Box3D box;
    if (gridData_ != nullptr && gridData_->GetNumberOfPoints() > 0) {
        SetBox3DFromVTKBound(gridData_->GetBounds(), box);
    }
    return box;
}

void TruncatedRegularGrid::SetProperty(geo3dml::ShapeProperty* prop, geo3dml::ShapeProperty::SamplingTarget t) {
	shapeHelper_.SetProperty(prop, t, GetID(), gridData_);
}

geo3dml::ShapeProperty* TruncatedRegularGrid::GetProperty(geo3dml::ShapeProperty::SamplingTarget t) const {
    return shapeHelper_.GetProperty(t, GetID(), gridData_.Get());
}

vtkUnstructuredGrid* TruncatedRegularGrid::GetVolumeData() const {
    return gridData_.Get();
}

