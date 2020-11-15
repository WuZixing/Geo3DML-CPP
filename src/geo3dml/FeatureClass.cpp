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

bool FeatureClass::GetMinimumBoundingRectangle(double& minX, double& minY, double& minZ, double& maxX, double& maxY, double& maxZ) const {
	size_t i = 0, numberOfFeature = features_.size();
	for (; i < numberOfFeature; ++i) {
		if (features_[i]->GetMinimumBoundingRectangle(minX, minY, minZ, maxX, maxY, maxZ)) {
			break;
		}
	}
	if (i >= numberOfFeature) {
		return false;
	}
	double x[2], y[2], z[2];
	for (++i; i < numberOfFeature; ++i) {
		if (!features_[i]->GetMinimumBoundingRectangle(x[0], y[0], z[0], x[1], y[1], z[1])) {
			continue;
		}
		if (x[0] < minX) {
			minX = x[0];
		}
		if (x[1] > maxX) {
			maxX = x[1];
		}
		if (y[0] < minY) {
			minY = y[0];
		}
		if (y[1] > maxY) {
			maxY = y[1];
		}
		if (z[0] < minZ) {
			minZ = z[0];
		}
		if (z[1] > maxZ) {
			maxZ = z[1];
		}
	}
	return true;
}
