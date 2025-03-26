#include <geo3dml/Model.h>
#include <geo3dml/Utils.h>

using namespace geo3dml;

Model::ModelType Model::NameToModelType(const std::string& n) {
	if (geo3dml::IsiEqual("Drill", n)) {
		return Drill;
	} else if (geo3dml::IsiEqual("Section", n)) {
		return Section;
	} else if (geo3dml::IsiEqual("3DModel", n) || geo3dml::IsiEqual("Map3D", n)) {
		return Model3D;
	} else if (geo3dml::IsiEqual("Isogram", n)) {
		return Isogram;
	} else {
		return Other;
	}
}

std::string Model::ModelTypeToName(Model::ModelType t) {
	switch (t) {
	case Drill:
		return "Drill";
	case Section:
		return "Section";
	case Model3D:
		return "3DModel";
	case Isogram:
		return "Isogram";
	default:
		return "Other";
	}
}

Model::Model() {
	type_ = Other;
}

Model::~Model() {
	std::vector<FeatureRelation*>::const_iterator ritor = featureRelations_.cbegin();
	while (ritor != featureRelations_.cend()) {
		delete* ritor;
		ritor++;
	}
	std::vector<FeatureClass*>::const_iterator fitor = featureClasses_.cbegin();
	while (fitor != featureClasses_.cend()) {
		delete * fitor;
		fitor++;
	}
}

void Model::SetName(const std::string& name) {
	name_ = name;
}

const std::string& Model::GetName() const {
	return name_;
}

void Model::SetType(ModelType t) {
	type_ = t;
}

Model::ModelType Model::GetType() const {
	return type_;
}

void Model::AddFeatureClass(FeatureClass* f) {
	if (f == NULL)
		return;
	std::vector<FeatureClass*>::const_iterator citor = featureClasses_.cbegin();
	while (citor != featureClasses_.cend()) {
		if (*citor == f)
			return;
		citor++;
	}
	f->SetParentModel(GetID());
	featureClasses_.push_back(f);
}

int Model::GetFeatureClassCount() const {
	return (int)featureClasses_.size();
}

FeatureClass* Model::GetFeatureClassAt(int i) const {
	return featureClasses_.at(i);
}

FeatureClass* Model::GetFeatureClass(const std::string& id) const {
	std::vector<FeatureClass*>::const_iterator citor = featureClasses_.cbegin();
	while (citor != featureClasses_.cend()) {
		if ((*citor)->GetID() == id) {
			return *citor;
		}
		citor++;
	}
	return NULL;
}

FeatureClass* Model::RemoveFeatureClass(const std::string& id) {
	FeatureClass* fc = nullptr;
	std::vector<FeatureClass*>::const_iterator citor = featureClasses_.cbegin();
	while (citor != featureClasses_.cend()) {
		if ((*citor)->GetID() == id) {
			fc = *citor;
			featureClasses_.erase(citor);
			break;
		}
		citor++;
	}
	return fc;
}

Feature* Model::FindFeatureById(const std::string& id) {
	Feature* feature = nullptr;
	for (auto citor = featureClasses_.cbegin(); citor != featureClasses_.cend(); ++citor) {
		feature = (*citor)->GetFeature(id);
		if (feature != nullptr) {
			break;
		}
	}
	return feature;
}

void Model::AddFeatureRelation(FeatureRelation* fr) {
	if (fr == nullptr)
		return;
	std::vector<FeatureRelation*>::const_iterator citor = featureRelations_.cbegin();
	while (citor != featureRelations_.cend()) {
		if (*citor == fr)
			return;
		citor++;
	}
	featureRelations_.push_back(fr);
}

int Model::GetFeatureRelationCount() const {
	return featureRelations_.size();
}

FeatureRelation* Model::GetFeatureRelation(int i) const {
	return featureRelations_.at(i);
}

FeatureRelation* Model::RemoveFeatureRelation(int i) {
	FeatureRelation* fr = featureRelations_.at(i);
	featureRelations_.erase(std::find(featureRelations_.begin(), featureRelations_.end(), fr));
	return fr;
}

Box3D Model::GetMinimumBoundingRectangle() const {
	Box3D box;
	for (size_t i = 0; i < featureClasses_.size(); ++i) {
		box.UnionWith(featureClasses_[i]->GetMinimumBoundingRectangle());
	}
	return box;
}

void Model::SetMetadata(const ModelMetadata& meta) {
	metadata_ = meta;
}

const ModelMetadata& Model::GetMetadata() const {
	return metadata_;
}

void Model::SetParentProject(const std::string& id) {
	parentProjectId_ = id;
}

const std::string& Model::GetParentProject() const {
	return parentProjectId_;
}
