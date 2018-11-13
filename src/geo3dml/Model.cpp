#include <geo3dml/Model.h>

using namespace geo3dml;

Model::ModelType Model::NameToModelType(const std::string& n) {
	if (_stricmp("Drill", n.c_str()) == 0) {
		return Drill;
	} else if (_stricmp("Section", n.c_str()) == 0) {
		return Section;
	} else if (_stricmp("3DModel", n.c_str()) == 0 || _stricmp("Map3D", n.c_str()) == 0) {
		return Model3D;
	} else if (_stricmp("Isogram", n.c_str()) == 0) {
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

void Model::SetBoundingBox(double minX, double minY, double minZ, double maxX, double maxY, double maxZ) {
	g3d_lock_guard lck(mtx_);
	box_[0] = minX;
	box_[1] = minY;
	box_[2] = minZ;
	box_[3] = maxX;
	box_[4] = maxY;
	box_[5] = maxZ;
}

void Model::GetBoundingBox(double& minX, double& minY, double& minZ, double& maxX, double& maxY, double& maxZ) {
	g3d_lock_guard lck(mtx_);
	if (box_[0] > box_[3]) {
		if (featureClasses_.empty()) {
			Context* ctx = GetContext();
			if (ctx != NULL && !ctx->IsDone()) {
				ctx->LoadMoreData();
			}
		}
		size_t numberOfFeatureClasses = featureClasses_.size();
		if (numberOfFeatureClasses < 1) {
			minX = maxX = 0;
			minY = maxY = 0;
			minZ = maxZ = 0;
			return;
		}
		featureClasses_[0]->GetBoundingBox(box_[0], box_[1], box_[2], box_[3], box_[4], box_[5]);
		for (size_t i = 1; i < numberOfFeatureClasses; ++i) {
			featureClasses_[0]->GetBoundingBox(minX, minY, minZ, maxX, maxY, maxZ);
			if (minX < box_[0]) {
				box_[0] = minX;
			}
			if (minY < box_[1]) {
				box_[1] = minY;
			}
			if (minZ < box_[2]) {
				box_[2] = minZ;
			}
			if (maxX > box_[3]) {
				box_[3] = maxX;
			}
			if (maxY > box_[4]) {
				box_[4] = maxY;
			}
			if (maxZ > box_[5]) {
				box_[5] = maxZ;
			}
		}
	}
	minX = box_[0];
	minY = box_[1];
	minZ = box_[2];
	maxX = box_[3];
	maxY = box_[4];
	maxZ = box_[5];
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

Model* Model::SetParentProject(const std::string& id) {
	g3d_lock_guard lck(mtx_);
	parentProjectId_ = id;
	return this;
}

std::string Model::GetParentProject() {
	g3d_lock_guard lck(mtx_);
	return parentProjectId_;
}
