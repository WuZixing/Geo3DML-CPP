// UTF-8编码
#include <geo3dml/RectifiedGrid.h>
#include <geo3dml/Matrix3x3.h>
#include <geo3dml/Utils.h>

using namespace geo3dml;

RectifiedGrid::RectifiedGrid(const Point3D& origin, const Vector3D& vecI, const Vector3D& vecJ, const Vector3D& vecK, int highI, int highJ, int highK, int lowI, int lowJ, int lowK) {
    origin_ = origin;
    axisI_ = vecI;
    axisJ_ = vecJ;
    axisK_ = vecK;
    highI_ = highI;
    highJ_ = highJ;
    highK_ = highK;
    lowI_ = lowI;
    lowJ_ = lowJ;
    lowK_ = lowK;
}

RectifiedGrid::RectifiedGrid(const Point3D& origin, double stepI, double stepJ, double stepK, int highI, int highJ, int highK, int lowI, int lowJ, int lowK) {
    origin_ = origin;
    axisI_ = Vector3D(stepI, 0, 0);
    axisJ_ = Vector3D(0, stepJ, 0);
    axisK_ = Vector3D(0, 0, stepK);
    highI_ = highI;
    highJ_ = highJ;
    highK_ = highK;
    lowI_ = lowI;
    lowJ_ = lowJ;
    lowK_ = lowK;
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

void RectifiedGrid::GetCellRange(int& lowI, int& lowJ, int& lowK, int& highI, int& highJ, int& highK) const {
    lowI = lowI_;
    lowJ = lowJ_;
    lowK = lowK_;
    highI = highI_;
    highJ = highJ_;
    highK = highK_;
}

Matrix4x4 RectifiedGrid::ComputeTransformMatrix() const {
    // 计算方法说明：Beginner's guide to mapping simplexes affinely (https://www.researchgate.net/publication/332410209_Beginner%27s_guide_to_mapping_simplexes_affinely).
    // 坐标变换的对应关系：p0 => pp0, p1 => pp1, p2 => pp2, p3 => pp3
    geo3dml::Point3D p0(-lowI_, -lowJ_, -lowK_);
    geo3dml::Point3D p1 = p0 + Vector3D(1, 0, 0);
    geo3dml::Point3D p2 = p0 + Vector3D(0, 1, 0);
    geo3dml::Point3D p3 = p0 + Vector3D(0, 0, 1);
    geo3dml::Point3D pp0 = origin_;
    geo3dml::Point3D pp1 = origin_ + axisI_;
    geo3dml::Point3D pp2 = origin_ + axisJ_;
    geo3dml::Point3D pp3 = origin_ + axisK_;

    Matrix4x4 mDenominator;
    mDenominator.Element(1, 1, p0.x);
    mDenominator.Element(2, 1, p0.y);
    mDenominator.Element(3, 1, p0.z);
    mDenominator.Element(4, 1, 1);
    mDenominator.Element(1, 2, p1.x);
    mDenominator.Element(2, 2, p1.y);
    mDenominator.Element(3, 2, p1.z);
    mDenominator.Element(4, 2, 1);
    mDenominator.Element(1, 3, p2.x);
    mDenominator.Element(2, 3, p2.y);
    mDenominator.Element(3, 3, p2.z);
    mDenominator.Element(4, 3, 1);
    mDenominator.Element(1, 4, p3.x);
    mDenominator.Element(2, 4, p3.y);
    mDenominator.Element(3, 4, p3.z);
    mDenominator.Element(4, 4, 1);
    double detDenominator = mDenominator.Determinant();
    if (IsZero(detDenominator)) {
        return Matrix4x4();
    }

    Matrix3x3 m00, m01, m02, m03;
    m00.Element(1, 1, p1.y);
    m00.Element(2, 1, p1.z);
    m00.Element(3, 1, 1);
    m00.Element(1, 2, p2.y);
    m00.Element(2, 2, p2.z);
    m00.Element(3, 2, 1);
    m00.Element(1, 3, p3.y);
    m00.Element(2, 3, p3.z);
    m00.Element(3, 3, 1);
    m01.Element(1, 1, p1.x);
    m01.Element(2, 1, p1.z);
    m01.Element(3, 1, 1);
    m01.Element(1, 2, p2.x);
    m01.Element(2, 2, p2.z);
    m01.Element(3, 2, 1);
    m01.Element(1, 3, p3.x);
    m01.Element(2, 3, p3.z);
    m01.Element(3, 3, 1);
    m02.Element(1, 1, p1.x);
    m02.Element(2, 1, p1.y);
    m02.Element(3, 1, 1);
    m02.Element(1, 2, p2.x);
    m02.Element(2, 2, p2.y);
    m02.Element(3, 2, 1);
    m02.Element(1, 3, p3.x);
    m02.Element(2, 3, p3.y);
    m02.Element(3, 3, 1);
    m03.Element(1, 1, p1.x);
    m03.Element(2, 1, p1.y);
    m03.Element(3, 1, p1.z);
    m03.Element(1, 2, p2.x);
    m03.Element(2, 2, p2.y);
    m03.Element(3, 2, p2.z);
    m03.Element(1, 3, p3.x);
    m03.Element(2, 3, p3.y);
    m03.Element(3, 3, p3.z);

    Matrix3x3 m10, m11, m12, m13;
    m10.Element(1, 1, p0.y);
    m10.Element(2, 1, p0.z);
    m10.Element(3, 1, 1);
    m10.Element(1, 2, p2.y);
    m10.Element(2, 2, p2.z);
    m10.Element(3, 2, 1);
    m10.Element(1, 3, p3.y);
    m10.Element(2, 3, p3.z);
    m10.Element(3, 3, 1);
    m11.Element(1, 1, p0.x);
    m11.Element(2, 1, p0.z);
    m11.Element(3, 1, 1);
    m11.Element(1, 2, p2.x);
    m11.Element(2, 2, p2.z);
    m11.Element(3, 2, 1);
    m11.Element(1, 3, p3.x);
    m11.Element(2, 3, p3.z);
    m11.Element(3, 3, 1);
    m12.Element(1, 1, p0.x);
    m12.Element(2, 1, p0.y);
    m12.Element(3, 1, 1);
    m12.Element(1, 2, p2.x);
    m12.Element(2, 2, p2.y);
    m12.Element(3, 2, 1);
    m12.Element(1, 3, p3.x);
    m12.Element(2, 3, p3.y);
    m12.Element(3, 3, 1);
    m13.Element(1, 1, p0.x);
    m13.Element(2, 1, p0.y);
    m13.Element(3, 1, p0.z);
    m13.Element(1, 2, p2.x);
    m13.Element(2, 2, p2.y);
    m13.Element(3, 2, p2.z);
    m13.Element(1, 3, p3.x);
    m13.Element(2, 3, p3.y);
    m13.Element(3, 3, p3.z);

    Matrix3x3 m20, m21, m22, m23;
    m20.Element(1, 1, p0.y);
    m20.Element(2, 1, p0.z);
    m20.Element(3, 1, 1);
    m20.Element(1, 2, p1.y);
    m20.Element(2, 2, p1.z);
    m20.Element(3, 2, 1);
    m20.Element(1, 3, p3.y);
    m20.Element(2, 3, p3.z);
    m20.Element(3, 3, 1);
    m21.Element(1, 1, p0.x);
    m21.Element(2, 1, p0.z);
    m21.Element(3, 1, 1);
    m21.Element(1, 2, p1.x);
    m21.Element(2, 2, p1.z);
    m21.Element(3, 2, 1);
    m21.Element(1, 3, p3.x);
    m21.Element(2, 3, p3.z);
    m21.Element(3, 3, 1);
    m22.Element(1, 1, p0.x);
    m22.Element(2, 1, p0.y);
    m22.Element(3, 1, 1);
    m22.Element(1, 2, p1.x);
    m22.Element(2, 2, p1.y);
    m22.Element(3, 2, 1);
    m22.Element(1, 3, p3.x);
    m22.Element(2, 3, p3.y);
    m22.Element(3, 3, 1);
    m23.Element(1, 1, p0.x);
    m23.Element(2, 1, p0.y);
    m23.Element(3, 1, p0.z);
    m23.Element(1, 2, p1.x);
    m23.Element(2, 2, p1.y);
    m23.Element(3, 2, p1.z);
    m23.Element(1, 3, p3.x);
    m23.Element(2, 3, p3.y);
    m23.Element(3, 3, p3.z);

    Matrix3x3 m30, m31, m32, m33;
    m30.Element(1, 1, p0.y);
    m30.Element(2, 1, p0.z);
    m30.Element(3, 1, 1);
    m30.Element(1, 2, p1.y);
    m30.Element(2, 2, p1.z);
    m30.Element(3, 2, 1);
    m30.Element(1, 3, p2.y);
    m30.Element(2, 3, p2.z);
    m30.Element(3, 3, 1);
    m31.Element(1, 1, p0.x);
    m31.Element(2, 1, p0.z);
    m31.Element(3, 1, 1);
    m31.Element(1, 2, p1.x);
    m31.Element(2, 2, p1.z);
    m31.Element(3, 2, 1);
    m31.Element(1, 3, p2.x);
    m31.Element(2, 3, p2.z);
    m31.Element(3, 3, 1);
    m32.Element(1, 1, p0.x);
    m32.Element(2, 1, p0.y);
    m32.Element(3, 1, 1);
    m32.Element(1, 2, p1.x);
    m32.Element(2, 2, p1.y);
    m32.Element(3, 2, 1);
    m32.Element(1, 3, p2.x);
    m32.Element(2, 3, p2.y);
    m32.Element(3, 3, 1);
    m33.Element(1, 1, p0.x);
    m33.Element(2, 1, p0.y);
    m33.Element(3, 1, p0.z);
    m33.Element(1, 2, p1.x);
    m33.Element(2, 2, p1.y);
    m33.Element(3, 2, p1.z);
    m33.Element(1, 3, p2.x);
    m33.Element(2, 3, p2.y);
    m33.Element(3, 3, p2.z);

    double detM00 = m00.Determinant();
    double detM01 = m01.Determinant();
    double detM02 = m02.Determinant();
    double detM03 = m03.Determinant();
    double detM10 = m10.Determinant();
    double detM11 = m11.Determinant();
    double detM12 = m12.Determinant();
    double detM13 = m13.Determinant();
    double detM20 = m20.Determinant();
    double detM21 = m21.Determinant();
    double detM22 = m22.Determinant();
    double detM23 = m23.Determinant();
    double detM30 = m30.Determinant();
    double detM31 = m31.Determinant();
    double detM32 = m32.Determinant();
    double detM33 = m33.Determinant();

    Vector3D col1, col2, col3, col4;
    col1.X(-pp0.x * detM00 + pp1.x * detM10 - pp2.x * detM20 + pp3.x * detM30);
    col1.Y(-pp0.y * detM00 + pp1.y * detM10 - pp2.y * detM20 + pp3.y * detM30);
    col1.Z(-pp0.z * detM00 + pp1.z * detM10 - pp2.z * detM20 + pp3.z * detM30);
    col2.X(pp0.x * detM01 - pp1.x * detM11 + pp2.x * detM21 - pp3.x * detM31);
    col2.Y(pp0.y * detM01 - pp1.y * detM11 + pp2.y * detM21 - pp3.y * detM31);
    col2.Z(pp0.z * detM01 - pp1.z * detM11 + pp2.z * detM21 - pp3.z * detM31);
    col3.X(-pp0.x * detM02 + pp1.x * detM12 - pp2.x * detM22 + pp3.x * detM32);
    col3.Y(-pp0.y * detM02 + pp1.y * detM12 - pp2.y * detM22 + pp3.y * detM32);
    col3.Z(-pp0.z * detM02 + pp1.z * detM12 - pp2.z * detM22 + pp3.z * detM32);
    col4.X(pp0.x * detM03 - pp1.x * detM13 + pp2.x * detM23 - pp3.x * detM33);
    col4.Y(pp0.y * detM03 - pp1.y * detM13 + pp2.y * detM23 - pp3.y * detM33);
    col4.Z(pp0.z * detM03 - pp1.z * detM13 + pp2.z * detM23 - pp3.z * detM33);

    Matrix4x4 t;
    t.Element(1, 1, -col1.X() / detDenominator);
    t.Element(2, 1, -col1.Y() / detDenominator);
    t.Element(3, 1, -col1.Z() / detDenominator);
    t.Element(4, 1, 0);
    t.Element(1, 2, -col2.X() / detDenominator);
    t.Element(2, 2, -col2.Y() / detDenominator);
    t.Element(3, 2, -col2.Z() / detDenominator);
    t.Element(4, 2, 0);
    t.Element(1, 3, -col3.X() / detDenominator);
    t.Element(2, 3, -col3.Y() / detDenominator);
    t.Element(3, 3, -col3.Z() / detDenominator);
    t.Element(4, 3, 0);
    t.Element(1, 4, -col4.X() / detDenominator);
    t.Element(2, 4, -col4.Y() / detDenominator);
    t.Element(3, 4, -col4.Z() / detDenominator);
    t.Element(4, 4, 1);

    return t;
}

Box3D RectifiedGrid::GetMinimumBoundingRectangle() const {
    Matrix4x4 t = ComputeTransformMatrix();
    Point3D pt0[8] = {
        Point3D(lowI_, lowJ_, lowK_), Point3D(highI_ + 1, lowJ_, lowK_), Point3D(highI_ + 1, highJ_ + 1, lowK_), Point3D(lowI_, highJ_ + 1, lowK_),
        Point3D(lowI_, lowJ_, highK_ + 1), Point3D(highI_ + 1, lowJ_, highK_ + 1), Point3D(highI_ + 1, highJ_ + 1, highK_ + 1), Point3D(lowI_, highJ_ + 1, highK_ + 1)
    };
    Point3D pt1[8];
    for (int i = 0; i < 8; ++i) {
        pt1[i].x = t.Element(1, 1) * pt0[i].x + t.Element(1, 2) * pt0[i].y + t.Element(1, 3) * pt0[i].z + t.Element(1, 4);
        pt1[i].y = t.Element(2, 1) * pt0[i].x + t.Element(2, 2) * pt0[i].y + t.Element(2, 3) * pt0[i].z + t.Element(2, 4);
        pt1[i].z = t.Element(3, 1) * pt0[i].x + t.Element(3, 2) * pt0[i].y + t.Element(3, 3) * pt0[i].z + t.Element(3, 4);
    }
    Box3D box;
    box.min = pt1[0];
    box.max = pt1[0];
    for (int i = 1; i < 8; ++i) {
        if (box.min.x > pt1[i].x) {
            box.min.x = pt1[i].x;
        }
        if (box.min.y > pt1[i].y) {
            box.min.y = pt1[i].y;
        }
        if (box.min.z > pt1[i].z) {
            box.min.z = pt1[i].z;
        }
        if (box.max.x < pt1[i].x) {
            box.max.x = pt1[i].x;
        }
        if (box.max.y < pt1[i].y) {
            box.max.y = pt1[i].y;
        }
        if (box.max.z < pt1[i].z) {
            box.max.z = pt1[i].z;
        }
    }
    return box;
}
