#include <geo3dml/Map.h>

using namespace geo3dml;

Map::Map() {
	for (int i = 0; i < 3; ++i) {
		box_[i] = 0;
		box_[i + 3] = -1;
	}
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

void Map::SetMinimumBoundingRectangle(double minX, double minY, double minZ, double maxX, double maxY, double maxZ) {
	g3d_lock_guard lck(mtx_);
	box_[0] = minX;
	box_[1] = minY;
	box_[2] = minZ;
	box_[3] = maxX;
	box_[4] = maxY;
	box_[5] = maxZ;
}

bool Map::GetMinimumBoundingRectangle(double& minX, double& minY, double& minZ, double& maxX, double& maxY, double& maxZ) {
	g3d_lock_guard lck(mtx_);
	if (box_[0] > box_[3]) {
		if (layers_.empty()) {
			Context* ctx = GetContext();
			if (ctx != NULL && !ctx->IsDone()) {
				ctx->LoadMoreData();
			}
		}
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
