#include <geo3dml/Map.h>

using namespace geo3dml;

Map::Map() {

}

Map::~Map() {
	std::vector<Layer*>::const_iterator layerItor = layers_.cbegin();
	while (layerItor != layers_.cend()) {
		delete *layerItor;
		++layerItor;
	}
}

void Map::SetName(const std::string& name) {
	name_ = name;
}

std::string Map::GetName() const {
	return name_;
}

void Map::SetDescription(const std::string& s) {
	description_ = s;
}

std::string Map::GetDescription() const {
	return description_;
}

void Map::SetParentProject(const std::string& id) {
	parentProjectId_ = id;
}

std::string Map::GetParentProject() const {
	return parentProjectId_;
}

void Map::AddLayer(Layer* layer) {
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

int Map::GetLayerCount() const {
	return (int)layers_.size();
}

Layer* Map::GetLayerAt(int i) const {
	return layers_.at(i);
}

Box3D Map::GetMinimumBoundingRectangle() const {
	Box3D box;
	for (size_t i = 0; i < layers_.size(); ++i) {
		box.UnionWith(layers_[i]->GetMinimumBoundingRectangle());
	}
	return box;
}
