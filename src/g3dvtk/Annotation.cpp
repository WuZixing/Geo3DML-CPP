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

std::string Annotation::GetLabelOfPointAt(int i) {
	return labels_->GetValue(i);
}

void Annotation::AddPoint(double x, double y, double z) {
	geo_->AddPoint(x, y, z);
}

int Annotation::GetPointCount() {
	return geo_->GetPointCount();
}

void Annotation::GetPointAt(int i, double& x, double& y, double& z) {
	geo_->GetPointAt(i, x, y, z);
}

bool Annotation::GetMinimumBoundingRectangle(double& minX, double& minY, double& minZ, double& maxX, double& maxY, double& maxZ) {
	return geo_->GetMinimumBoundingRectangle(minX, minY, minZ, maxX, maxY, maxZ);
}

void Annotation::SetProperty(geo3dml::ShapeProperty* prop, geo3dml::ShapeProperty::SamplingTarget t) {
	geo_->SetProperty(prop, t);
}

geo3dml::ShapeProperty* Annotation::GetProperty(geo3dml::ShapeProperty::SamplingTarget t) {
	return geo_->GetProperty(t);
}

vtkPolyData* Annotation::GetPolyData() {
	return geo_->GetPolyData();
}

void Annotation::ConfigLabelMapper(vtkLabeledDataMapper* mapper) {
	mapper->SetInputData(GetPolyData());
	mapper->SetLabelModeToLabelFieldData();
	mapper->SetFieldDataName(labels_->GetName());
}
