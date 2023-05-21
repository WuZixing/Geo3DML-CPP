// UTF-8编码
#pragma once

#include <geo3dml/RectifiedGrid.h>
#include <g3dvtk/ShapeHelper.h>
#include <vtkSmartPointer.h>
#include <vtkUniformGrid.h>

namespace g3dvtk {

    class RectifiedGrid : public geo3dml::RectifiedGrid {
    public:
        /// @see geo3dml::RectifiedGrid::RectifiedGrid
        RectifiedGrid(const geo3dml::Point3D& origin,
            int dimI, int dimJ, int dimK,
            const geo3dml::Vector3D& vecI, const geo3dml::Vector3D& vecJ, const geo3dml::Vector3D& vecK);
        /// @see geo3dml::RectifiedGrid::RectifiedGrid
        RectifiedGrid(const geo3dml::Point3D& origin, int dimI, int dimJ, int dimK, double stepI, double stepJ, double stepK);
        virtual ~RectifiedGrid();

        /// @name 实现基类 geo3dml::Geometry 定义的接口。
        //@{
        /// @see geo3dml::Geometry#SetProperty
        virtual void SetProperty(geo3dml::ShapeProperty* prop, geo3dml::ShapeProperty::SamplingTarget t) override;
        /// @see geo3dml::Geometry#GetProperty
        virtual geo3dml::ShapeProperty* GetProperty(geo3dml::ShapeProperty::SamplingTarget t) const override;
        //@}

    public:
        vtkUniformGrid* GetUniformGrid() const;

    private:
        vtkSmartPointer<vtkUniformGrid> uniformGrid_;
        ShapeHelper shapeHelper_;
    };
}
