#include <geo3dml/Map.h>

using namespace geo3dml;

Map::Map() {

}

Map::~Map() {
	g3d_lock_guard lck(mtx_);
	std::vector<Layer*>::const_iterator layerItor = layers_.cbegin();
	while (layerItor != layers_.cend()) {
		delete *layerItor;
		++layerItor;
	}
}

void Map::SetName(const std::string& name) {
	g3d_lock_guard lck(mtx_);
	name_ = name;
}

std::string Map::GetName() {
	g3d_lock_guard lck(mtx_);
	return name_;
}

void Map::SetDescription(const std::string& s) {
	g3d_lock_guard lck(mtx_);
	description_ = s;
}

std::string Map::GetDescription() {
	g3d_lock_guard lck(mtx_);
	return description_;
}

void Map::SetParentProject(const std::string& id) {
	g3d_lock_guard lck(mtx_);
	parentProjectId_ = id;
}

std::string Map::GetParentProject() {
	g3d_lock_guard lck(mtx_);
	return parentProjectId_;
}

void Map::AddLayer(Layer* layer) {
	g3d_lock_guard lck(mtx_);
	std::vector<Layer*>::const_iterator citor = layers_.cbegin();
	while (citor != layers_.cend()) {
		if (*citor == layer) {
			return;
		}
		++citor;
	}
	layer->SetParentMap(GetID());
	layers_.push_back(layer);
}

int Map::GetLayerCount() {
	g3d_lock_guard lck(mtx_);
	return (int)layers_.size();
}

Layer* Map::GetLayerAt(int i) {
	g3d_lock_guard lck(mtx_);
	return layers_.at(i);
}
