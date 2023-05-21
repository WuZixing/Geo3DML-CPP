#pragma once

#include <geo3dml/MultiLineString.h>
#include <vtkPolyData.h>
#include <g3dvtk/ShapeHelper.h>

namespace g3dvtk {

	class MultiLineString : public geo3dml::MultiLineString {
	public:
		MultiLineString();
		virtual ~MultiLineString();

	public:
		/// @name Methods inherited from geo3dml::MultiLineString.
		//@{
		virtual int AddLineString();
		virtual void AddVertexToLineString(int lineIndex, double x, double y, double z);
		virtual int GetLineStringCount() const;
		virtual int GetVertexCountOfLineString(int lineIndex) const;
		virtual void GetVertexOfLineString(int lineIndex, int vertexIndex, double& x, double& y, double& z) const;
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
