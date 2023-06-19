#include <geo3dml/Layer.h>
#include <geo3dml/ObjectFactory.h>
#include <sstream>

using namespace geo3dml;

Layer::Layer() {
	bindingFeatureClass_ = NULL;
}

Layer::~Layer() {
	std::vector<Style*>::const_iterator styleItor = styles_.cbegin();
	while (styleItor != styles_.cend()) {
		delete *styleItor;
		++styleItor;
	}
	DeleteAllActors();
}

void Layer::SetName(const std::string& name) {
	name_ = name;
}

std::string Layer::GetName() const {
	return name_;
}

void Layer::BindFeatureClass(FeatureClass* fc) {
	bindingFeatureClass_ = fc;
}

FeatureClass* Layer::GetBindingFeatureClass() const {
	return bindingFeatureClass_;
}

void Layer::SetBindingFeatureClassID(const std::string& featureClassID) {
	bindingFeatureClassID_ = featureClassID;
}

std::string Layer::GetBindingFeatureClassID() const {
	return bindingFeatureClassID_;
}

void Layer::SetParentMap(const std::string& id) {
	parentMapId_ = id;
}

std::string Layer::GetParentMap() const {
	return parentMapId_;
}

void Layer::AddStyle(Style* style) {
	if (style == NULL) {
		return;
	}
	std::vector<Style*>::const_iterator styleItor = styles_.cbegin();
	while (styleItor != styles_.cend()) {
		if (*styleItor == style) {
			return;
		}
		++styleItor;
	}
	styles_.push_back(style);
}

int Layer::GetStyleCount() const {
	return (int)styles_.size();
}

Style* Layer::GetStyleAt(int i) const {
	return styles_.at(i);
}

Box3D Layer::GetMinimumBoundingRectangle() const {
	Box3D box;
	if (bindingFeatureClass_ != nullptr) {
		box = bindingFeatureClass_->GetMinimumBoundingRectangle();
	}
	return box;
}

void Layer::AddActor(Actor* actor) {
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

int Layer::GetActorCount() const {
	return (int)actors_.size();
}

Actor* Layer::GetActorAt(int i) const {
	return actors_.at(i);
}

void Layer::BuildActorsFromFeatures(ObjectFactory* g3dFactory) {
	RebuildActorsFromFeaturesByStyle(-1, g3dFactory);
}

void Layer::RebuildActorsFromFeaturesByStyle(int styleIndex, ObjectFactory* g3dFactory) {
	if (bindingFeatureClass_ == NULL) {
		return;
	}
	Style* style = NULL;
	if (styleIndex >= 0 && styleIndex < styles_.size()) {
		style = styles_[styleIndex];
	}
	DeleteAllActors();
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
		geo3dml::Geometry* geo = feature->GetGeometry();
		if (geo != nullptr) {
			geo3dml::Actor* actor = g3dFactory->NewActor();
			actor->SetName(feature->GetName() + "_" + geo->GetName());
			actor->BindGeometry(feature, geo, sym);
			AddActor(actor);
		} else {
			geo3dml::Actor* actor = g3dFactory->NewActor();
			actor->SetName(feature->GetName());
			actor->BindGeometry(feature, nullptr, nullptr);
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
