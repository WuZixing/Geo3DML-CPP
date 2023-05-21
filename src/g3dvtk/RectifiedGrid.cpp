// UTF-8编码
#include <g3dvtk/RectifiedGrid.h>

using namespace g3dvtk;

RectifiedGrid::RectifiedGrid(const geo3dml::Point3D& origin,
    int dimI, int dimJ, int dimK,
    const geo3dml::Vector3D& vecI, const geo3dml::Vector3D& vecJ, const geo3dml::Vector3D& vecK)
    : geo3dml::RectifiedGrid(origin, dimI, dimJ, dimK, vecI, vecJ, vecK) {
    // vtkImageData的局部坐标系定义：
    // 原点：(0, 0, 0)
    // X轴：(1, 0, 0)
    // Y轴：(0, 1, 0)
    // Z轴：(0, 0, 1)
    // 局部坐标系下网格单元是边长为单位长度的立方体。
    uniformGrid_ = vtkSmartPointer<vtkUniformGrid>::New();
    uniformGrid_->SetDimensions(dimI + 1, dimJ + 1, dimK + 1);	// vtkImageData needs to know dimensions in points.
    uniformGrid_->SetOrigin(0, 0, 0);
    uniformGrid_->SetSpacing(1, 1, 1);
}

RectifiedGrid::RectifiedGrid(const geo3dml::Point3D& origin, int dimI, int dimJ, int dimK, double stepI, double stepJ, double stepK)
    : geo3dml::RectifiedGrid(origin, dimI, dimJ, dimK, stepI, stepJ, stepK) {
    uniformGrid_ = vtkSmartPointer<vtkUniformGrid>::New();
    uniformGrid_->SetDimensions(dimI + 1, dimJ + 1, dimK + 1);	// vtkImageData needs to know dimensions in points.
    uniformGrid_->SetOrigin(0, 0, 0);
    uniformGrid_->SetSpacing(1, 1, 1);
}

RectifiedGrid::~RectifiedGrid() {

}

void RectifiedGrid::SetProperty(geo3dml::ShapeProperty* prop, geo3dml::ShapeProperty::SamplingTarget t) {
    shapeHelper_.SetProperty(prop, t, GetID(), uniformGrid_);
}

geo3dml::ShapeProperty* RectifiedGrid::GetProperty(geo3dml::ShapeProperty::SamplingTarget t) const {
    return shapeHelper_.GetProperty(t, GetID(), uniformGrid_);
}

vtkUniformGrid* RectifiedGrid::GetUniformGrid() const {
    return uniformGrid_.Get();
}
