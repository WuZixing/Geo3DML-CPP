#include <geo3dml/FeatureClass.h>

using namespace geo3dml;

FeatureClass::FeatureClass() {

}

FeatureClass::~FeatureClass() {
	std::vector<Feature*>::const_iterator citor = features_.cbegin();
	while (citor != features_.cend()) {
		delete *citor;
		citor++;
	}
}

FeatureClass& FeatureClass::SetName(const std::string& name) {
	name_ = name;
	return *this;
}

std::string FeatureClass::GetName() const {
	return name_;
}

FeatureClass& FeatureClass::AddFeature(Feature* f) {
	if (f == NULL)
		return *this;
	std::vector<Feature*>::const_iterator citor = features_.cbegin();
	while (citor != features_.cend()) {
		if (*citor == f)
			return *this;
		citor++;
	}
	features_.push_back(f);
	f->SetParentFeatureClass(GetID());
	return *this;
}

int FeatureClass::GetFeatureCount() const {
	return (int)features_.size();
}

Feature* FeatureClass::GetFeatureAt(int i) const {
	return features_.at(i);
}

Feature* FeatureClass::GetFeature(const std::string& id) const {
	std::vector<Feature*>::const_iterator citor = features_.cbegin();
	while (citor != features_.cend()) {
		if ((*citor)->GetID() == id) {
			return *citor;
		}
		citor++;
	}
	return NULL;
}

FeatureClass& FeatureClass::SetParentModel(const std::string& id) {
	parentModelId_ = id;
	return *this;
}

std::string FeatureClass::GetParentModel() const {
	return parentModelId_;
}

FeatureClass& FeatureClass::AddField(const Field& f) {
	fields_.push_back(f);
	return *this;
}

int FeatureClass::GetFieldCount() const {
	return (int)fields_.size();
}

const Field& FeatureClass::GetFieldAt(int i) const {
	return fields_.at(i);
}

Box3D FeatureClass::GetMinimumBoundingRectangle() const {
	Box3D box;
	for (size_t i = 0; i < features_.size(); ++i) {
		box.UnionWith(features_[i]->GetMinimumBoundingRectangle());
	}
	return box;
}
