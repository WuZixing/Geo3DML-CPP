// UTF-8编码
#include <geo3dml/Feature.h>

using namespace geo3dml;

Feature::Feature() {
	geometry_ = nullptr;
}

Feature::~Feature() {
	if (geometry_ != nullptr) {
		delete geometry_;
	}
}

Feature& Feature::SetName(const std::string& name) {
	name_ = name;
	return *this;
}

const std::string& Feature::GetName() const {
	return name_;
}

Feature& Feature::SetGeometry(Geometry* g) {
	if (geometry_ != nullptr && geometry_ != g) {
		delete geometry_;
	}
	geometry_ = g;
	return *this;
}

Geometry* Feature::GetGeometry() const {
	return geometry_;
}

Feature& Feature::SetParentFeatureClass(const std::string& id) {
	parentFeatureClassId_ = id;
	return *this;
}

const std::string& Feature::GetParentFeatureClass() const {
	return parentFeatureClassId_;
}

Feature& Feature::SetField(const FieldValue& fv) {
	fieldValues_[fv.FieldName()] = fv;
	return *this;
}

const FieldValue* Feature::GetField(const std::string& name) const {
	if (fieldValues_.find(name) != fieldValues_.cend()) {
		return &(fieldValues_.find(name)->second);
	} else {
		return nullptr;
	}
}

std::vector<std::string> Feature::GetFieldNames() const {
	std::vector<std::string> names;
	std::map<std::string, geo3dml::FieldValue>::const_iterator citor = fieldValues_.cbegin();
	while (citor != fieldValues_.cend()) {
		names.push_back(citor->first);
		++citor;
	}
	return names;
}

Box3D Feature::GetMinimumBoundingRectangle() const {
	if (geometry_ != nullptr) {
		return geometry_->GetMinimumBoundingRectangle();
	} else {
		return Box3D();
	}
}
