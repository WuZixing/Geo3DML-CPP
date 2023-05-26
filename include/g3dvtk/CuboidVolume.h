// UTF-8编码
#pragma once

#include <vtkUnstructuredGrid.h>
#include <geo3dml/CuboidVolume.h>
#include <g3dvtk/ShapeHelper.h>

namespace g3dvtk {
    /// @brief 基于VTK数据结构的CuboidVolume类型实现。
    class CuboidVolume : public geo3dml::CuboidVolume {
    public:
        CuboidVolume();
        virtual ~CuboidVolume();

        /// @name 实现父类 geo3dml::CuboidVolume 定义的接口。
        ///@{
        virtual int AppendVertex(double x, double y, double z) override;
        virtual int GetVertexCount() const override;
        virtual bool GetVertexAt(int i, double& x, double& y, double& z) const override;
        virtual int AppendCuboid(int v1, int v2, int v3, int v4, int v5, int v6, int v7, int v8) override;
        virtual int GetCuboidCount() const override;
        virtual bool GetCuboidAt(int i, int& v1, int& v2, int& v3, int& v4, int& v5, int& v6, int& v7, int& v8) const override;
        ///@}

        /// @name 实现基类 geo3dml::Geometry 定义的接口。
        //@{
        virtual geo3dml::Box3D GetMinimumBoundingRectangle() const override;
        virtual void SetProperty(geo3dml::ShapeProperty* prop, geo3dml::ShapeProperty::SamplingTarget t) override;
        virtual geo3dml::ShapeProperty* GetProperty(geo3dml::ShapeProperty::SamplingTarget t) const override;
        //@}

        vtkUnstructuredGrid* GetVolumeData() const;

    private:
        vtkSmartPointer<vtkUnstructuredGrid> grid_;
        ShapeHelper shapeHelper_;
    };
}
