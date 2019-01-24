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
		virtual void SetPosition(double x, double y, double z);
		virtual void GetPosition(double& x, double& y, double& z);
		//@}

		/// @name Methods inherited from geo3dml::Geometry.
		//@{
		virtual bool GetMinimumBoundingRectangle(double& minX, double& minY, double& minZ, double& maxX, double& maxY, double& maxZ);
		virtual void SetProperty(geo3dml::ShapeProperty* prop, geo3dml::ShapeProperty::SamplingTarget t);
		virtual geo3dml::ShapeProperty* GetProperty(geo3dml::ShapeProperty::SamplingTarget t);
		//@}

		vtkPolyData* GetPolyData();

	private:
		vtkSmartPointer<vtkPolyData> polyData_;
		ShapeHelper shapeHelper_;
	};
}
