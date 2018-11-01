#include <g3dvtk/ShapeHelper.h>
#include <g3dvtk/ShapeProperty.h>
#include <vtkPointData.h>
#include <vtkCellData.h>

using namespace g3dvtk;

ShapeHelper::ShapeHelper() {
	vertexProperty_ = NULL;
	voxelProperty_ = NULL;
	edgeProperty_ = NULL;
	faceProperty_ = NULL;
}

ShapeHelper::~ShapeHelper() {
	if (vertexProperty_ != NULL) {
		delete vertexProperty_;
		vertexProperty_ = NULL;
	}
	if (voxelProperty_ != NULL) {
		delete voxelProperty_;
		voxelProperty_ = NULL;
	}
	if (edgeProperty_ != NULL) {
		delete edgeProperty_;
		edgeProperty_ = NULL;
	}
	if (faceProperty_ != NULL) {
		delete faceProperty_;
		faceProperty_ = NULL;
	}
}

void ShapeHelper::SetProperty(geo3dml::ShapeProperty* prop, geo3dml::ShapeProperty::SamplingTarget t, const std::string& shapeId, vtkDataSet* dataSet) {
	ShapeProperty* g3dvtkProp = NULL;
	if (prop != NULL) {
		prop->Target(shapeId, t);
		g3dvtkProp = dynamic_cast<ShapeProperty*>(prop);
	}
	switch (t) {
	case geo3dml::ShapeProperty::Vertex:
		if (vertexProperty_ != NULL) {
			delete vertexProperty_;
		}
		if (g3dvtkProp != NULL) {
			g3dvtkProp->BindDataSet(dataSet->GetPointData());
		}
		vertexProperty_ = prop;
		break;
	case geo3dml::ShapeProperty::Edge:
		if (edgeProperty_ != NULL) {
			delete edgeProperty_;
		}
		if (g3dvtkProp != NULL) {
			g3dvtkProp->BindDataSet(dataSet->GetCellData());
		}
		edgeProperty_ = prop;
		break;
	case geo3dml::ShapeProperty::Face:
		if (faceProperty_ != NULL) {
			delete faceProperty_;
		}
		if (g3dvtkProp != NULL) {
			g3dvtkProp->BindDataSet(dataSet->GetCellData());
		}
		faceProperty_ = prop;
		break;
	case geo3dml::ShapeProperty::Voxel:
		if (voxelProperty_ != NULL) {
			delete voxelProperty_;
		}
		if (g3dvtkProp != NULL) {
			g3dvtkProp->BindDataSet(dataSet->GetCellData());
		}
		voxelProperty_ = prop;
		break;
	default:
		break;
	}
}

geo3dml::ShapeProperty* ShapeHelper::GetProperty(geo3dml::ShapeProperty::SamplingTarget t, const std::string& shapeId, vtkDataSet* dataSet) {
	switch (t) {
	case geo3dml::ShapeProperty::Vertex:
		return vertexProperty_;
	case geo3dml::ShapeProperty::Edge:
		return edgeProperty_;
	case geo3dml::ShapeProperty::Face:
		return faceProperty_;
	case geo3dml::ShapeProperty::Voxel:
		return voxelProperty_;
	default:
		return NULL;
	}
}
