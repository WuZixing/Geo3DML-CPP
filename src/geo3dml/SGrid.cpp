// UTF-8编码
#include <geo3dml/SGrid.h>

using namespace geo3dml;

SGrid::SGrid() {
    planeGridAzimuth_ = 0;
    planeGridCellSizeX_ = planeGridCellSizeY_ = 0;
    planeGridCellNumberX_ = planeGridCellNumberY_ = 0;
}

SGrid::~SGrid() {

}

void SGrid::SetPlaneGridOrigin(const Point3D& pt) {
    planeGridOrigin_ = pt;
}

const Point3D& SGrid::GetPlaneGridOrigin() const {
    return planeGridOrigin_;
}

void SGrid::SetPlaneGridAzimuth(double degree) {
    planeGridAzimuth_ = degree;
}

double SGrid::GetPlaneGridAzimuth() const {
    return planeGridAzimuth_;
}

void SGrid::SetPlaneGridCellSize(double xSize, double ySize) {
    planeGridCellSizeX_ = xSize;
    planeGridCellSizeY_ = ySize;
}

void SGrid::GetPlaneGridCellSize(double& xSize, double& ySize) const {
    xSize = planeGridCellSizeX_;
    ySize = planeGridCellSizeY_;
}

void SGrid::SetPlaneGridCellNumber(int xNumber, int yNumber) {
    planeGridCellNumberX_ = xNumber;
    planeGridCellNumberY_ = yNumber;
}

void SGrid::GetPlaneGridCellNumber(int& xNumber, int& yNumber) const {
    xNumber = planeGridCellNumberX_;
    yNumber = planeGridCellNumberY_;
}
