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
	std::vector<FeatureClass*>::const_iterator citor = featureClasses_.cbegin();
	while (citor != featureClasses_.cend()) {
		delete *citor;
		citor++;
	}
}

void Model::SetName(const std::string& name) {
	name_ = name;
}

std::string Model::GetName() const {
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

void Model::RemoveFeatureClass(const std::string& id) {
	std::vector<FeatureClass*>::const_iterator citor = featureClasses_.cbegin();
	while (citor != featureClasses_.cend()) {
		if ((*citor)->GetID() == id) {
			featureClasses_.erase(citor);
			break;
		}
		citor++;
	}
}

bool Model::GetMinimumBoundingRectangle(double& minX, double& minY, double& minZ, double& maxX, double& maxY, double& maxZ) const {
	size_t i = 0, numberOfFeatureClasses = featureClasses_.size();
	for (; i < numberOfFeatureClasses; ++i) {
		if (featureClasses_[i]->GetMinimumBoundingRectangle(minX, minY, minZ, maxX, maxY, maxZ)) {
			break;
		}
	}
	if (i >= numberOfFeatureClasses) {
		return false;
	}
	double x[2], y[2], z[2];
	for (++i; i < numberOfFeatureClasses; ++i) {
		if (!featureClasses_[i]->GetMinimumBoundingRectangle(x[0], y[0], z[0], x[1], y[1], z[1])) {
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

std::string Model::GetDateStamp() const {
	return dateStamp_;
}

void Model::SetDateStamp(const std::string& s) {
	dateStamp_ = s;
}

std::string Model::GetDescription() const {
	return description_;
}

void Model::SetDescription(const std::string& s) {
	description_ = s;
}

std::string Model::GetVersion() const {
	return version_;
}

void Model::SetVersion(const std::string& s) {
	version_ = s;
}

std::string Model::GetToolName() const {
	return toolName_;
}

void Model::SetToolName(const std::string& s) {
	toolName_ = s;
}

std::string Model::GetToolVersion() const {
	return toolVersion_;
}

void Model::SetToolVersion(const std::string& s) {
	toolVersion_ = s;
}

void Model::SetParentProject(const std::string& id) {
	parentProjectId_ = id;
}

std::string Model::GetParentProject() const {
	return parentProjectId_;
}
