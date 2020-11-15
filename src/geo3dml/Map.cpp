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

bool Map::GetMinimumBoundingRectangle(double& minX, double& minY, double& minZ, double& maxX, double& maxY, double& maxZ) const {
	size_t i = 0, numberOfLayers = layers_.size();
	for (; i < numberOfLayers; ++i) {
		if (layers_[i]->GetMinimumBoundingRectangle(minX, minY, minZ, maxX, maxY, maxZ)) {
			break;
		}
	}
	if (i >= numberOfLayers) {
		return false;
	}
	double x[2], y[2], z[2];
	for (++i; i < numberOfLayers; ++i) {
		if (!layers_[i]->GetMinimumBoundingRectangle(x[0], y[0], z[0], x[1], y[1], z[1])) {
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
