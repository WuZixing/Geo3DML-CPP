// UTF-8编码
#include <geo3dml/Feature.h>

using namespace geo3dml;

Feature::Feature() {
	geometry_ = nullptr;
}

Feature::~Feature() {
	// std::vector<Geometry*>::const_iterator citor = geometries_.cbegin();
	// while (citor != geometries_.end()) {
	//     delete *citor;
	//	   citor++;
	// }
	if (geometry_ != nullptr) {
		delete geometry_;
	}
}

Feature& Feature::SetName(const std::string& name) {
	name_ = name;
	return *this;
}

std::string Feature::GetName() const {
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

/*
Feature& Feature::AddGeometry(Geometry* g) {
	if (g == NULL)
		return *this;
	std::vector<Geometry*>::const_iterator citor = geometries_.cbegin();
	while (citor != geometries_.end()) {
		if (*citor == g)
			return *this;
		citor++;
	}
	geometries_.push_back(g);
	return *this;
}

int Feature::GetGeometryCount() const {
	return (int)geometries_.size();
}

Geometry* Feature::GetGeometryAt(int i) const {
	return geometries_.at(i);
}
*/

Feature& Feature::SetParentFeatureClass(const std::string& id) {
	parentFeatureClassId_ = id;
	return *this;
}

std::string Feature::GetParentFeatureClass() const {
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
	// Box3D box;
	// for (size_t i = 0; i < geometries_.size(); ++i) {
	// 	box.UnionWith(geometries_[i]->GetMinimumBoundingRectangle());
	// }
	// return box;
	if (geometry_ != nullptr) {
		return geometry_->GetMinimumBoundingRectangle();
	} else {
		return Box3D();
	}
}
