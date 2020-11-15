#include <geo3dml/SceneStyle.h>
#include <cmath>

using namespace geo3dml;

SceneStyle::SceneStyle() {

}

SceneStyle::~SceneStyle() {

}

SceneStyle& SceneStyle::SetBackgroundColor(const Color& c) {
	color_ = c;
	return *this;
}

Color SceneStyle::GetBackgroundColor() const {
	return color_;
}

SceneStyle& SceneStyle::AddLight(const Light& lit) {
	if (lights_.size() > 7) {
		return *this;
	}
	lights_.push_back(lit);
	return *this;
}

int SceneStyle::GetLightCount() const {
	return (int)lights_.size();
}

Light SceneStyle::GetLightAt(int i) const {
	return lights_.at(i);
}
