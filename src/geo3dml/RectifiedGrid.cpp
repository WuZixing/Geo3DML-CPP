// UTF-8编码
#include <geo3dml/RectifiedGrid.h>

using namespace geo3dml;

RectifiedGrid::RectifiedGrid(const Point3D& origin, const Vector3D& vecI, const Vector3D& vecJ, const Vector3D& vecK, int dimI, int dimJ, int dimK) {
    origin_ = origin;
    axisI_ = vecI;
    axisJ_ = vecJ;
    axisK_ = vecK;
    dimI_ = dimI;
    dimJ_ = dimJ;
    dimK_ = dimK;
}

RectifiedGrid::~RectifiedGrid() {

}

const Point3D& RectifiedGrid::Origin() const {
    return origin_;
}

const Vector3D& RectifiedGrid::AxisI() const {
    return axisI_;
}

const Vector3D& RectifiedGrid::AxisJ() const {
    return axisJ_;
}
const Vector3D& RectifiedGrid::AxisK() const {
    return axisK_;
}

void RectifiedGrid::GetDimensions(int& i, int& j, int& k) const {
    i = dimI_;
    j = dimJ_;
    k = dimK_;
}

Matrix4x4 RectifiedGrid::ComputeTransformMatrix() const {
    return Matrix4x4();
}

bool RectifiedGrid::GetMinimumBoundingRectangle(double& minX, double& minY, double& minZ, double& maxX, double& maxY, double& maxZ) const {
    return false;
}
