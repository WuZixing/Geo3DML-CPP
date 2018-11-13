#include <geo3dml/Project.h>

using namespace geo3dml;

Project::Project() {

}

Project::~Project() {
	std::vector<Model*>::const_iterator citor = models_.cbegin();
	while (citor != models_.cend()) {
		delete *citor;
		citor++;
	}
}

void Project::SetName(const std::string& name) {
	g3d_lock_guard lck(mtx_);
	name_ = name;
}

std::string Project::GetName() {
	g3d_lock_guard lck(mtx_);
	return name_;
}

void Project::SetDescription(const std::string& desc) {
	g3d_lock_guard lck(mtx_);
	description_ = desc;
}

std::string Project::GetDescription() {
	g3d_lock_guard lck(mtx_);
	return description_;
}

void Project::AddModel(Model* model) {
	g3d_lock_guard lck(mtx_);
	if (model == NULL)
		return;
	std::vector<Model*>::const_iterator citor = models_.cbegin();
	while (citor != models_.cend()) {
		if (*citor == model)
			return;
		citor++;
	}
	std::string pId = GetID();
	model->SetParentProject(pId);
	models_.push_back(model);
}

int Project::GetModelCount() {
	g3d_lock_guard lck(mtx_);
	return (int)models_.size();
}

Model* Project::GetModelAt(int i) {
	g3d_lock_guard lck(mtx_);
	return models_.at(i);
}

Model* Project::RemoveModelAt(int i) {
	g3d_lock_guard lck(mtx_);
	std::vector<Model*>::const_iterator citor = models_.cbegin();
	while (citor != models_.cend() && i > 0) {
		++citor;
		--i;
	}
	Model* model = NULL;
	if (citor != models_.end()) {
		model = *citor;
		models_.erase(citor);
	}
	return model;
}

SceneStyle& Project::GetSceneStyle() {
	g3d_lock_guard lck(mtx_);
	return sceneStyle_;
}

bool Project::GetBoundingBox(double& minX, double& minY, double& minZ, double& maxX, double& maxY, double& maxZ) {
	g3d_lock_guard lck(mtx_);
	size_t i = 0, numberOfModels = models_.size();
	for (; i < numberOfModels; ++i) {
		if (models_[i]->GetBoundingBox(minX, minY, minZ, maxX, maxY, maxZ)) {
			break;
		}
	}
	if (i >= numberOfModels) {
		return false;
	}
	double x[2], y[2], z[2];
	for (++i; i < numberOfModels; ++i) {
		if (!models_[i]->GetBoundingBox(x[0], y[0], z[0], x[1], y[1], z[1])) {
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
