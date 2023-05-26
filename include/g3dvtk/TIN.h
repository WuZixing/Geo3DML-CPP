#pragma once

#include <geo3dml/TIN.h>
#include <vtkPolyData.h>
#include <g3dvtk/ShapeHelper.h>

namespace g3dvtk {

	class TIN : public geo3dml::TIN {
	public:
		TIN();
		virtual ~TIN();

		/// @name Methods inherited from geo3dml::TIN.
		//@{
		virtual void AppendVertex(double x, double y, double z) override;
		virtual int GetVertexCount() const override;
		virtual void GetVertexAt(int i, double& x, double& y, double& z) const override;
		virtual void AppendTriangle(int v1, int v2, int v3) override;
		virtual int GetTriangleCount() const override;
		virtual void GetTriangleAt(int i, int& vertex1, int& vertex2, int& vertex3) const override;
		//@}

		/// @name Methods inherited from geo3dml::Geometry.
		//@{
		virtual geo3dml::Box3D GetMinimumBoundingRectangle() const override;
		virtual void SetProperty(geo3dml::ShapeProperty* prop, geo3dml::ShapeProperty::SamplingTarget t) override;
		virtual geo3dml::ShapeProperty* GetProperty(geo3dml::ShapeProperty::SamplingTarget t) const override;
		//@}

		vtkPolyData* GetPolyData() const;

	private:
		vtkSmartPointer<vtkPolyData> polyData_;
		ShapeHelper shapeHelper_;
	};
}
