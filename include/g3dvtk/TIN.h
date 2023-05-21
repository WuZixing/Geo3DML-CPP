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
		virtual void AddVertex(int index, double x, double y, double z);
		virtual int GetVertexCount() const;
		virtual void GetVertexAt(int i, double& x, double& y, double& z) const;
		virtual void AddTriangle(int index, int vertex1, int vertex2, int vertex3);
		virtual int GetTriangleCount() const;
		virtual void GetTriangleAt(int i, int& vertex1, int& vertex2, int& vertex3) const;
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
