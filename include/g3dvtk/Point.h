#pragma once

#include <geo3dml/Point.h>
#include <vtkPolyData.h>
#include <g3dvtk/ShapeHelper.h>

namespace g3dvtk {

	class Point : public geo3dml::Point {
	public:
		Point();
		virtual ~Point();

	public:
		/// @name Methods inherited from geo3dml::Point.
		//@{
		virtual void SetPosition(double x, double y, double z) override;
		virtual void GetPosition(double& x, double& y, double& z) const override;
		virtual double GetX() const override;
		virtual double GetY() const override;
		virtual double GetZ() const override;
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
