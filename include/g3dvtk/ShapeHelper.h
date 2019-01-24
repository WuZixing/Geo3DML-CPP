#pragma once

#include <geo3dml/ShapeProperty.h>
#include <vtkDataSet.h>

namespace g3dvtk {

	class ShapeHelper {
	public:
		ShapeHelper();
		virtual ~ShapeHelper();

	public:
		void SetProperty(geo3dml::ShapeProperty* prop, geo3dml::ShapeProperty::SamplingTarget t, const std::string& shapeId, vtkDataSet* dataSet);
		geo3dml::ShapeProperty* GetProperty(geo3dml::ShapeProperty::SamplingTarget t, const std::string& shapeId, vtkDataSet* dataSet);

	private:
		geo3dml::ShapeProperty* vertexProperty_;
		geo3dml::ShapeProperty* voxelProperty_;
		geo3dml::ShapeProperty* edgeProperty_;
		geo3dml::ShapeProperty* faceProperty_;
	};
}