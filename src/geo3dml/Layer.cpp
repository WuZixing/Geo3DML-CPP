#include <geo3dml/Layer.h>
#include <geo3dml/ObjectFactory.h>
#include <sstream>

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
	DeleteAllActors();
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

void Layer::SetBindingFeatureClassID(const std::string& featureClassID) {
	g3d_lock_guard lck(mtx_);
	bindingFeatureClassID_ = featureClassID;
}

std::string Layer::GetBindingFeatureClassID() {
	g3d_lock_guard lck(mtx_);
	return bindingFeatureClassID_;
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

bool Layer::GetMinimumBoundingRectangle(double& minX, double& minY, double& minZ, double& maxX, double& maxY, double& maxZ) {
	g3d_lock_guard lck(mtx_);
	if (bindingFeatureClass_ != NULL) {
		return bindingFeatureClass_->GetMinimumBoundingRectangle(minX, minY, minZ, maxX, maxY, maxZ);
	} else {
		return false;
	}
}

void Layer::AddActor(Actor* actor) {
	g3d_lock_guard lck(mtx_);
	if (actor == NULL) {
		return;
	}
	std::vector<Actor*>::const_iterator actorItor = actors_.cbegin();
	while (actorItor != actors_.cend()) {
		if (*actorItor == actor) {
			return;
		}
		++actorItor;
	}
	actors_.push_back(actor);
}

int Layer::GetActorCount() {
	g3d_lock_guard lck(mtx_);
	return (int)actors_.size();
}

Actor* Layer::GetActorAt(int i) {
	g3d_lock_guard lck(mtx_);
	return actors_.at(i);
}

void Layer::BuildActorsFromFeatures(ObjectFactory* g3dFactory) {
	RebuildActorsFromFeaturesByStyle(-1, g3dFactory);
}

void Layer::RebuildActorsFromFeaturesByStyle(int styleIndex, ObjectFactory* g3dFactory) {
	g3d_lock_guard lck(mtx_);
	if (bindingFeatureClass_ == NULL) {
		return;
	}
	Geo3DStyle* style = NULL;
	if (styleIndex >= 0 && styleIndex < styles_.size()) {
		style = styles_[styleIndex];
	}
	DeleteAllActors();
	std::ostringstream ostr;
	int numberOfFeatures = bindingFeatureClass_->GetFeatureCount();
	for (int f = 0; f < numberOfFeatures; ++f) {
		geo3dml::Feature* feature = bindingFeatureClass_->GetFeatureAt(f);
		geo3dml::Symbolizer* sym = NULL;
		if (style != NULL) {
			StyleRule* rule = style->MatchWithFeature(feature);
			if (rule != NULL) {
				sym = rule->GetSymbolizer();
			}
		}
		int numberOfGeometries = feature->GetGeometryCount();
		for (int g = 0; g < numberOfGeometries; ++g) {
			geo3dml::Geometry* geo = feature->GetGeometryAt(g);
			geo3dml::Actor* actor = g3dFactory->NewActor();
			ostr.str("");
			ostr << feature->GetName() << "_" << geo->GetName() << "[LOD-" << geo->GetLODLevel() << "]";
			actor->SetName(ostr.str());	
			actor->BindGeometry(feature, geo, sym);
			AddActor(actor);
		}
	}
}

void Layer::DeleteAllActors() {
	std::vector<Actor*>::const_iterator actorItor = actors_.cbegin();
	while (actorItor != actors_.cend()) {
		delete *actorItor;
		++actorItor;
	}
	actors_.clear();
}
