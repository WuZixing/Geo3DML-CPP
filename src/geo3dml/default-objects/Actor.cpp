// UTF-8编码
#include "Actor.h"

using namespace geo3dml::geometry;

Actor::Actor() {
    bindingFeature_ = NULL;
    bindingGeometry_ = NULL;
    symbolizer_ = NULL;
    isVisible_ = true;
}

Actor::~Actor() {

}

void Actor::BindGeometry(Feature* feature, Geometry* geo, Symbolizer* sym) {
    bindingFeature_ = feature;
    bindingGeometry_ = geo;
    symbolizer_ = sym;
}

geo3dml::Feature* Actor::GetBindingFeature() const {
    return bindingFeature_;
}

geo3dml::Geometry* Actor::GetBindingGeometry() const {
    return bindingGeometry_;
}

bool Actor::IsVisible() const {
    return isVisible_;
}

void Actor::SetVisible(bool show) {
    isVisible_ = show;
}

geo3dml::Symbolizer* Actor::MakeSymbozier() const {
    if (symbolizer_ != nullptr) {
        return symbolizer_->Clone();
    } else {
        return nullptr;
    }
}
