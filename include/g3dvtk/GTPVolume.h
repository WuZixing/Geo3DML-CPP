// UTF-8编码
#pragma once

#include <geo3dml/GTPVolume.h>
#include <vtkUnstructuredGrid.h>
#include <g3dvtk/ShapeHelper.h>

namespace g3dvtk {

    /// @brief 基于VTK数据结构的广义三棱柱数据结构实现。
    class GTPVolume : public geo3dml::GTPVolume {
    public:
        GTPVolume();
        virtual ~GTPVolume();

    public:
        /// @name 实现geo3dml::GTPVolume定义的虚函数。
        ///@{
        virtual int AppendVertex(double x, double y, double z) override;
        virtual int GetVertexCount() const override;
        virtual bool GetVertexAt(int i, double& x, double& y, double& z) const override;
        virtual int AppendPrism(int topVertex1, int topVertex2, int topVertex3, int bottomVertex1, int bottomVertex2, int bottomVertex3) override;
        virtual int GetPrismCount() const override;
        virtual bool GetPrismAt(int i, int& topVertex1, int& topVertex2, int& topVertex3, int& bottomVertex1, int& bottomVertex2, int& bottomVertex3) const override;
        ///@}

        /// @name 实现geo3dml::Geometry定义的虚函数。
        ///@{
        virtual geo3dml::Box3D GetMinimumBoundingRectangle() const override;
        virtual void SetProperty(geo3dml::ShapeProperty* prop, geo3dml::ShapeProperty::SamplingTarget t) override;
        virtual geo3dml::ShapeProperty* GetProperty(geo3dml::ShapeProperty::SamplingTarget t) const override;
        ///@}

        vtkUnstructuredGrid* GetVolumeData() const;

    private:
        vtkSmartPointer<vtkUnstructuredGrid> gridData_;
        ShapeHelper shapeHelper_;
    };
}
