#pragma once

#include <geo3dml/Annotation.h>
#include <g3dvtk/MultiPoint.h>
#include <vtkStringArray.h>
#include <vtkLabeledDataMapper.h>

namespace g3dvtk {

	class Annotation : public geo3dml::Annotation {
	public:
		Annotation();
		virtual ~Annotation();

	public:
		/// @name Methods inherited from geo3dml::Annotation.
		//@{
		virtual void SetLabelOfPointAt(int i, const std::string& s);
		virtual std::string GetLabelOfPointAt(int i);
		//@}

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
		void ConfigLabelMapper(vtkLabeledDataMapper* mapper);

	private:
		g3dvtk::MultiPoint* geo_;
		vtkSmartPointer<vtkStringArray> labels_;
	};
}
