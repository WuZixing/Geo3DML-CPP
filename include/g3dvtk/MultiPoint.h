#pragma once

#include <geo3dml/MultiPoint.h>
#include <vtkPolyData.h>
#include <g3dvtk/ShapeHelper.h>

namespace g3dvtk {

	class MultiPoint : public geo3dml::MultiPoint {
	public:
		MultiPoint();
		virtual ~MultiPoint();

	public:
		/// @name Methods inherited from geo3dml::MultiPoint.
		//@{
		virtual void AddPoint(double x, double y, double z);
		virtual int GetPointCount();
		virtual void GetPointAt(int i, double& x, double& y, double& z);
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