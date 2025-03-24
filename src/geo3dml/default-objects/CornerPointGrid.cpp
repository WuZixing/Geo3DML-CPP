// UTF-8编码
#include "CornerPointGrid.h"

using namespace geo3dml::geometry;

CornerPointGrid::CornerPointGrid() {
    dimI_ = 0;
    dimJ_ = 0;
    dimK_ = 0;
}

CornerPointGrid::CornerPointGrid(int dimI, int dimJ, int dimK) {
    dimI_ = 0;
    dimJ_ = 0;
    dimK_ = 0;
    Init(dimI, dimJ, dimK);
}

CornerPointGrid::~CornerPointGrid() {

}

bool CornerPointGrid::Init(int dimI, int dimJ, int dimK) {
    if (dimI < 1 || dimJ < 1 || dimK < 1) {
        return false;
    }
    dimI_ = dimI;
    dimJ_ = dimJ;
    dimK_ = dimK;
    // 一共有 (dimI + 1) * (dimJ + 1)条Pillar。
    pillars_.reserve((dimI + 1) * (dimJ + 1));
    // 一共有 dimI * dimJ * dimK 个体元。
    cells_.resize(dimI * dimJ * dimK);
    return true;
}

void CornerPointGrid::GetDimensions(int& i, int& j, int& k) const {
    i = dimI_;
    j = dimJ_;
    k = dimK_;
}

void CornerPointGrid::AddNextPillar(double headPos[3], double tailPos[3]) {
    Pillar pillar;
    DoubleArrayToPoint(headPos, pillar.head);
    DoubleArrayToPoint(tailPos, pillar.tail);
    pillars_.emplace_back(pillar);
}

void CornerPointGrid::AddNextCell(
    int i, int j, int k,
    double bottomFrontLeft[3], double bottomFrontRight[3],
    double bottomBackLeft[3], double bottomBackRight[3],
    double topFrontLeft[3], double topFrontRight[3],
    double topBackLeft[3], double topBackRight[3],
    bool isValid) {
    Cell cell;
    DoubleArrayToPoint(bottomFrontLeft, cell.corners[0]);
    DoubleArrayToPoint(bottomFrontRight, cell.corners[1]);
    DoubleArrayToPoint(bottomBackLeft, cell.corners[2]);
    DoubleArrayToPoint(bottomBackRight, cell.corners[3]);
    DoubleArrayToPoint(topFrontLeft, cell.corners[4]);
    DoubleArrayToPoint(topFrontRight, cell.corners[5]);
    DoubleArrayToPoint(topBackLeft, cell.corners[6]);
    DoubleArrayToPoint(topBackRight, cell.corners[7]);
    cell.isValid = isValid;
    int cellIndex = GetCellIndex(i, j, k);
    cells_[cellIndex] = cell;
}

void CornerPointGrid::SetCellValidation(int i, int j, int k, bool beValid) {
    int cellIndex = GetCellIndex(i, j, k);
    cells_[cellIndex].isValid = beValid;
}

void CornerPointGrid::GetPillarAt(int i, int j, double headPos[3], double tailPos[3]) const {
    int pillarIndex = j * (dimI_ + 1) * i;
    const Pillar& pillar = pillars_.at(pillarIndex);
    PointToDoubleArray(pillar.head, headPos);
    PointToDoubleArray(pillar.tail, tailPos);
}

void CornerPointGrid::GetCellAt(int i, int j, int k,
    double bottomFrontLeft[3], double bottomFrontRight[3],
    double bottomBackLeft[3], double bottomBackRight[3],
    double topFrontLeft[3], double topFrontRight[3],
    double topBackLeft[3], double topBackRight[3],
    bool& isValid) const {
    int cellIndex = GetCellIndex(i, j, k);
    const Cell& cell = cells_.at(cellIndex);
    PointToDoubleArray(cell.corners[0], bottomFrontLeft);
    PointToDoubleArray(cell.corners[1], bottomFrontRight);
    PointToDoubleArray(cell.corners[2], bottomBackLeft);
    PointToDoubleArray(cell.corners[3], bottomBackRight);
    PointToDoubleArray(cell.corners[4], topFrontLeft);
    PointToDoubleArray(cell.corners[5], topFrontRight);
    PointToDoubleArray(cell.corners[6], topBackLeft);
    PointToDoubleArray(cell.corners[7], topBackRight);
    isValid = cell.isValid;
}

geo3dml::Box3D CornerPointGrid::GetMinimumBoundingRectangle() const {
    geo3dml::Box3D box;
    for (auto citor = cells_.cbegin(); citor != cells_.cend(); ++citor) {
        for (int n = 0; n < 8; ++n) {
            box.ExtendWith(citor->corners[n]);
        }
    }
    return box;
}

void CornerPointGrid::DoubleArrayToPoint(const double pos[3], Point3D& pt) const {
    pt.x = pos[0];
    pt.y = pos[1];
    pt.z = pos[2];
}

void CornerPointGrid::PointToDoubleArray(const Point3D& pt, double pos[3]) const {
    pos[0] = pt.x;
    pos[1] = pt.y;
    pos[2] = pt.z;
}

int CornerPointGrid::GetCellIndex(int i, int j, int k) const {
    return k * (dimJ_ * dimI_) + j * dimI_ + i;
}
