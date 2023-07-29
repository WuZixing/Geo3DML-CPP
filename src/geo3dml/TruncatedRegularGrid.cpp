// UTF-8编码
#include <geo3dml/TruncatedRegularGrid.h>

using namespace geo3dml;

TruncatedRegularGrid::TruncatedRegularGrid() {
    planeGridAzimuth_ = 0;
    planeGridCellSizeX_ = planeGridCellSizeY_ = 0;
    planeGridCellNumberX_ = planeGridCellNumberY_ = 0;
}

TruncatedRegularGrid::~TruncatedRegularGrid() {

}

void TruncatedRegularGrid::SetPlaneGridOrigin(const Point3D& pt) {
    planeGridOrigin_ = pt;
}

const Point3D& TruncatedRegularGrid::GetPlaneGridOrigin() const {
    return planeGridOrigin_;
}

void TruncatedRegularGrid::SetPlaneGridAzimuth(double degree) {
    planeGridAzimuth_ = degree;
}

double TruncatedRegularGrid::GetPlaneGridAzimuth() const {
    return planeGridAzimuth_;
}

void TruncatedRegularGrid::SetPlaneGridCellSize(double xSize, double ySize) {
    planeGridCellSizeX_ = xSize;
    planeGridCellSizeY_ = ySize;
}

void TruncatedRegularGrid::GetPlaneGridCellSize(double& xSize, double& ySize) const {
    xSize = planeGridCellSizeX_;
    ySize = planeGridCellSizeY_;
}

void TruncatedRegularGrid::SetPlaneGridCellNumber(int xNumber, int yNumber) {
    planeGridCellNumberX_ = xNumber;
    planeGridCellNumberY_ = yNumber;
}

void TruncatedRegularGrid::GetPlaneGridCellNumber(int& xNumber, int& yNumber) const {
    xNumber = planeGridCellNumberX_;
    yNumber = planeGridCellNumberY_;
}
