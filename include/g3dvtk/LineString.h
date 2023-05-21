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
		virtual void AddVertex(double x, double y, double z);
		virtual int GetVertexCount() const;
		virtual void GetVertexAt(int i, double& x, double& y, double& z) const;
		//@}

		/// @name Methods inherited from geo3dml::Geometry.
		//@{
		virtual geo3dml::Box3D GetMinimumBoundingRectangle() const override;
		virtual void SetProperty(geo3dml::ShapeProperty* prop, geo3dml::ShapeProperty::SamplingTarget t);
		virtual geo3dml::ShapeProperty* GetProperty(geo3dml::ShapeProperty::SamplingTarget t) const;
		//@}

		vtkPolyData* GetPolyData() const;

	private:
		vtkSmartPointer<vtkPolyData> polyData_;
		ShapeHelper shapeHelper_;
	};
}
