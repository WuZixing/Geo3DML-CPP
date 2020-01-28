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
	for (int i = 0; i < 3; ++i) {
		box_[i] = 0;
		box_[i + 3] = -1;
	}
}

Model::~Model() {
	std::vector<FeatureClass*>::const_iterator citor = featureClasses_.cbegin();
	while (citor != featureClasses_.cend()) {
		delete *citor;
		citor++;
	}
}

void Model::SetName(const std::string& name) {
	g3d_lock_guard lck(mtx_);
	name_ = name;
}

std::string Model::GetName() {
	g3d_lock_guard lck(mtx_);
	return name_;
}

void Model::SetType(ModelType t) {
	g3d_lock_guard lck(mtx_);
	type_ = t;
}

Model::ModelType Model::GetType() {
	g3d_lock_guard lck(mtx_);
	return type_;
}

void Model::AddFeatureClass(FeatureClass* f) {
	g3d_lock_guard lck(mtx_);
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

int Model::GetFeatureClassCount() {
	g3d_lock_guard lck(mtx_);
	if (featureClasses_.empty()) {
		Context* ctx = GetContext();
		if (ctx != NULL && !ctx->IsDone()) {
			ctx->LoadMoreData();
		}
	}
	return (int)featureClasses_.size();
}

FeatureClass* Model::GetFeatureClassAt(int i) {
	g3d_lock_guard lck(mtx_);
	if (featureClasses_.empty()) {
		Context* ctx = GetContext();
		if (ctx != NULL && !ctx->IsDone()) {
			ctx->LoadMoreData();
		}
	}
	return featureClasses_.at(i);
}

FeatureClass* Model::GetFeatureClass(const std::string& id) {
	g3d_lock_guard lck(mtx_);
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
	g3d_lock_guard lck(mtx_);
	std::vector<FeatureClass*>::const_iterator citor = featureClasses_.cbegin();
	while (citor != featureClasses_.cend()) {
		if ((*citor)->GetID() == id) {
			featureClasses_.erase(citor);
			break;
		}
		citor++;
	}
}

void Model::SetMinimumBoundingRectangle(double minX, double minY, double minZ, double maxX, double maxY, double maxZ) {
	g3d_lock_guard lck(mtx_);
	box_[0] = minX;
	box_[1] = minY;
	box_[2] = minZ;
	box_[3] = maxX;
	box_[4] = maxY;
	box_[5] = maxZ;
}

bool Model::GetMinimumBoundingRectangle(double& minX, double& minY, double& minZ, double& maxX, double& maxY, double& maxZ) {
	g3d_lock_guard lck(mtx_);
	if (box_[0] > box_[3]) {
		if (featureClasses_.empty()) {
			Context* ctx = GetContext();
			if (ctx != NULL && !ctx->IsDone()) {
				ctx->LoadMoreData();
			}
		}
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
		box_[0] = minX;
		box_[1] = minY;
		box_[2] = minZ;
		box_[3] = maxX;
		box_[4] = maxY;
		box_[5] = maxZ;
	} else {
		minX = box_[0];
		minY = box_[1];
		minZ = box_[2];
		maxX = box_[3];
		maxY = box_[4];
		maxZ = box_[5];
	}
	return true;
}

std::string Model::GetDateStamp() {
	g3d_lock_guard lck(mtx_);
	return dateStamp_;
}

void Model::SetDateStamp(const std::string& s) {
	g3d_lock_guard lck(mtx_);
	dateStamp_ = s;
}

std::string Model::GetDescription() {
	g3d_lock_guard lck(mtx_);
	return description_;
}

void Model::SetDescription(const std::string& s) {
	g3d_lock_guard lck(mtx_);
	description_ = s;
}

std::string Model::GetVersion() {
	g3d_lock_guard lck(mtx_);
	return version_;
}

void Model::SetVersion(const std::string& s) {
	g3d_lock_guard lck(mtx_);
	version_ = s;
}

std::string Model::GetToolName() {
	g3d_lock_guard lck(mtx_);
	return toolName_;
}

void Model::SetToolName(const std::string& s) {
	g3d_lock_guard lck(mtx_);
	toolName_ = s;
}

std::string Model::GetToolVersion() {
	g3d_lock_guard lck(mtx_);
	return toolVersion_;
}

void Model::SetToolVersion(const std::string& s) {
	g3d_lock_guard lck(mtx_);
	toolVersion_ = s;
}

void Model::SetParentProject(const std::string& id) {
	g3d_lock_guard lck(mtx_);
	parentProjectId_ = id;
}

std::string Model::GetParentProject() {
	g3d_lock_guard lck(mtx_);
	return parentProjectId_;
}
