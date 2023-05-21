#include <geo3dml/Project.h>
#include <geo3dml/ObjectFactory.h>

using namespace geo3dml;

Project::Project() {

}

Project::~Project() {
	std::vector<Model*>::const_iterator citor = models_.cbegin();
	while (citor != models_.cend()) {
		delete *citor;
		citor++;
	}
	std::vector<Map*>::const_iterator mapItor = maps_.cbegin();
	while (mapItor != maps_.cend()) {
		delete *mapItor;
		mapItor++;
	}
}

void Project::SetName(const std::string& name) {
	name_ = name;
}

std::string Project::GetName() const {
	return name_;
}

void Project::SetDescription(const std::string& desc) {
	description_ = desc;
}

std::string Project::GetDescription() const {
	return description_;
}

void Project::AddModel(Model* model) {
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

int Project::GetModelCount() const {
	return (int)models_.size();
}

Model* Project::GetModelAt(int i) const {
	return models_.at(i);
}

FeatureClass* Project::FindFeatureClass(const std::string& id) const {
	std::vector<Model*>::const_iterator citor = models_.cbegin();
	while (citor != models_.cend()) {
		FeatureClass* featureClass = (*citor)->GetFeatureClass(id);
		if (featureClass != NULL) {
			return featureClass;
		}
		citor++;
	}
	return NULL;
}

Model* Project::RemoveModelAt(int i) {
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
	return sceneStyle_;
}

Box3D Project::GetMinimumBoundingRectangle() const {
	Box3D box;
	for (size_t i = 0; i < models_.size(); ++i) {
		box.UnionWith(models_[i]->GetMinimumBoundingRectangle());
	}
	return box;
}

void Project::AddMap(Map* map) {
	if (map == NULL)
		return;
	std::vector<Map*>::const_iterator citor = maps_.cbegin();
	while (citor != maps_.cend()) {
		if (*citor == map)
			return;
		citor++;
	}
	std::string pId = GetID();
	map->SetParentProject(pId);
	maps_.push_back(map);
}

int Project::GetMapCount() const {
	return (int)maps_.size();
}

Map* Project::GetMapAt(int i) const {
	return maps_.at(i);
}

Map* Project::RemoveMapAt(int i) {
	std::vector<Map*>::const_iterator citor = maps_.cbegin();
	while (citor != maps_.cend() && i > 0) {
		++citor;
		--i;
	}
	Map* map = NULL;
	if (citor != maps_.end()) {
		map = *citor;
		maps_.erase(citor);
	}
	return map;
}

void Project::BindFeatureClassesToLayers(ObjectFactory* g3dFactory) {
	std::vector<Map*>::const_iterator mapItor = maps_.cbegin();
	while (mapItor != maps_.cend()) {
		int numberOfLayers = (*mapItor)->GetLayerCount();
		for (int i = 0; i < numberOfLayers; ++i) {
			geo3dml::Layer* layer = (*mapItor)->GetLayerAt(i);
			if (layer->GetBindingFeatureClass() == NULL) {
				FeatureClass* fc = FindFeatureClass(layer->GetBindingFeatureClassID());
				layer->BindFeatureClass(fc);
				layer->RebuildActorsFromFeaturesByStyle(0, g3dFactory);
			}
		}
		++mapItor;
	}
}
