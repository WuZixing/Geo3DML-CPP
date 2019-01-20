#include <geo3dml/Layer.h>

using namespace geo3dml;

Layer::Layer() {
	bindingFeatureClass_ = NULL;
}

Layer::~Layer() {
	std::vector<Geo3DStyle*>::const_iterator styleItor = styles_.cbegin();
	while (styleItor != styles_.cend()) {
		delete *styleItor;
		++styleItor;
	}
}

void Layer::SetName(const std::string& name) {
	g3d_lock_guard lck(mtx_);
	name_ = name;
}

std::string Layer::GetName() {
	g3d_lock_guard lck(mtx_);
	return name_;
}

void Layer::BindFeatureClass(FeatureClass* fc) {
	g3d_lock_guard lck(mtx_);
	bindingFeatureClass_ = fc;
}

FeatureClass* Layer::GetBindingFeatureClass() {
	g3d_lock_guard lck(mtx_);
	return bindingFeatureClass_;
}

void Layer::SetParentMap(const std::string& id) {
	g3d_lock_guard lck(mtx_);
	parentMapId_ = id;
}

std::string Layer::GetParentMap() {
	g3d_lock_guard lck(mtx_);
	return parentMapId_;
}

void Layer::AddStyle(Geo3DStyle* style) {
	g3d_lock_guard lck(mtx_);
	if (style == NULL) {
		return;
	}
	std::vector<Geo3DStyle*>::const_iterator styleItor = styles_.cbegin();
	while (styleItor != styles_.cend()) {
		if (*styleItor == style) {
			return;
		}
		++styleItor;
	}
	styles_.push_back(style);
}

int Layer::GetStyleCount() {
	g3d_lock_guard lck(mtx_);
	return (int)styles_.size();
}

Geo3DStyle* Layer::GetStyleAt(int i) {
	g3d_lock_guard lck(mtx_);
	return styles_.at(i);
}
