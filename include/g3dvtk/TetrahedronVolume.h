// UTF-8编码
#pragma once

#include <vtkUnstructuredGrid.h>
#include <geo3dml/TetrahedronVolume.h>
#include <g3dvtk/ShapeHelper.h>

namespace g3dvtk {
    /// @brief 基于VTK数据结构的TetrahedronVolume类型实现。
    class TetrahedronVolume : public geo3dml::TetrahedronVolume {
    public:
        TetrahedronVolume();
        virtual ~TetrahedronVolume();

        /// @name 实现父类 geo3dml::TetrahedronVolume 定义的接口。
        ///@{
        virtual int AppendVertex(double x, double y, double z) override;
        virtual int GetVertexCount() const override;
        virtual bool GetVertexAt(int i, double& x, double& y, double& z) const override;
        virtual int AppendTetrahedron(int v1, int v2, int v3, int v4) override;
        virtual int GetTetrahedronCount() const override;
        virtual bool GetTetrahedronAt(int i, int& v1, int& v2, int& v3, int& v4) const override;
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
