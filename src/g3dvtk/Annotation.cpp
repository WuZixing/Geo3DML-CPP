#include <g3dvtk/Annotation.h>
#include <g3dvtk/ShapeProperty.h>
#include <vtkPointData.h>

using namespace g3dvtk;

Annotation::Annotation() {
	geo_ = new g3dvtk::MultiPoint();
	labels_ = vtkSmartPointer<vtkStringArray>::New();
	labels_->SetName("#label");
	GetPolyData()->GetPointData()->AddArray(labels_);
}

Annotation::~Annotation() {
	delete geo_;
}

void Annotation::SetLabelOfPointAt(int i, const std::string& s) {
	labels_->InsertValue(i, s.c_str());
}

std::string Annotation::GetLabelOfPointAt(int i) const {
	return labels_->GetValue(i);
}

void Annotation::AddPoint(double x, double y, double z) {
	geo_->AddPoint(x, y, z);
}

int Annotation::GetPointCount() const {
	return geo_->GetPointCount();
}

void Annotation::GetPointAt(int i, double& x, double& y, double& z) const {
	geo_->GetPointAt(i, x, y, z);
}

geo3dml::Box3D Annotation::GetMinimumBoundingRectangle() const {
	return geo_->GetMinimumBoundingRectangle();
}

void Annotation::SetProperty(geo3dml::ShapeProperty* prop, geo3dml::ShapeProperty::SamplingTarget t) {
	geo_->SetProperty(prop, t);
}

geo3dml::ShapeProperty* Annotation::GetProperty(geo3dml::ShapeProperty::SamplingTarget t) const {
	return geo_->GetProperty(t);
}

vtkPolyData* Annotation::GetPolyData() const {
	vtkPolyData* polyData = geo_->GetPolyData();
	if (polyData != NULL && polyData->NeedToBuildCells()) {
		polyData->BuildCells();
	}
	return polyData;
}

void Annotation::ConfigLabelMapper(vtkLabeledDataMapper* mapper) const {
	mapper->SetInputData(GetPolyData());

	if (labels_->GetNumberOfValues() > 0) {
		mapper->SetLabelModeToLabelFieldData();
		mapper->SetFieldDataName(labels_->GetName());
	}
}
