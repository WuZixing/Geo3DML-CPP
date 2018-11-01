#include <geo3dml/Feature.h>

using namespace geo3dml;

Feature::Feature() {

}

Feature::~Feature() {
	std::vector<Geometry*>::const_iterator citor = geometries_.cbegin();
	while (citor != geometries_.end()) {
		delete *citor;
		citor++;
	}
	std::map<std::string, geo3dml::FieldValue*>::iterator itor = fieldValues_.begin();
	while (itor != fieldValues_.end()) {
		delete itor->second;
		itor->second = NULL;
		++itor;
	}
}

Feature& Feature::SetName(const std::string& name) {
	g3d_lock_guard lck(mtx_);
	name_ = name;
	return *this;
}

std::string Feature::GetName() {
	g3d_lock_guard lck(mtx_);
	return name_;
}

Feature& Feature::AddGeometry(Geometry* g) {
	g3d_lock_guard lck(mtx_);
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

int Feature::GetGeometryCount() {
	g3d_lock_guard lck(mtx_);
	return (int)geometries_.size();
}

Geometry* Feature::GetGeometryAt(int i) {
	g3d_lock_guard lck(mtx_);
	return geometries_.at(i);

}

Feature& Feature::SetParentFeatureClass(const std::string& id) {
	g3d_lock_guard lck(mtx_);
	parentFeatureClassId_ = id;
	return *this;
}

std::string Feature::GetParentFeatureClass() {
	g3d_lock_guard lck(mtx_);
	return parentFeatureClassId_;
}

Feature& Feature::SetField(FieldValue* fv) {
	if (fv == NULL) {
		return *this;
	}
	g3d_lock_guard lck(mtx_);
	fieldValues_[fv->Name()] = fv;
	return *this;
}

FieldValue* Feature::GetField(const std::string& name) {
	g3d_lock_guard lck(mtx_);
	if (fieldValues_.find(name) != fieldValues_.cend()) {
		return fieldValues_[name];
	} else {
		return NULL;
	}
}

std::vector<std::string> Feature::GetFieldNames() {
	g3d_lock_guard lck(mtx_);
	std::vector<std::string> names;
	std::map<std::string, geo3dml::FieldValue*>::const_iterator citor = fieldValues_.cbegin();
	while (citor != fieldValues_.cend()) {
		names.push_back(citor->first);
		++citor;
	}
	return names;
}
