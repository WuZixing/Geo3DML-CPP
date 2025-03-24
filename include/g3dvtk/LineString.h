#pragma once

#include <geo3dml/LineString.h>
#include <vtkPolyData.h>
#include <g3dvtk/ShapeHelper.h>

namespace g3dvtk {

	class LineString : public geo3dml::LineString {
	public:
		LineString();
		virtual ~LineString();

	public:
		/// @name Method inherited from geo3dml::LineString.
		//@{
		virtual void AddVertex(double x, double y, double z)  override;
		virtual int GetVertexCount() const  override;
		virtual void GetVertexAt(int i, double& x, double& y, double& z) const  override;
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
