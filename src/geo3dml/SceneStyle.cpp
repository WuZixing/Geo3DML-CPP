#include <geo3dml/SceneStyle.h>
#include <cmath>

using namespace geo3dml;

SceneStyle::SceneStyle() {

}

SceneStyle::~SceneStyle() {

}

SceneStyle& SceneStyle::SetBackgroundColor(const Color& c) {
	std::lock_guard<std::recursive_mutex> lck(mtx_);
	color_ = c;
	return *this;
}

Color SceneStyle::GetBackgroundColor() {
	std::lock_guard<std::recursive_mutex> lck(mtx_);
	return color_;
}

SceneStyle& SceneStyle::AddLight(const Light& lit) {
	std::lock_guard<std::recursive_mutex> lck(mtx_);
	if (lights_.size() > 7) {
		return *this;
	}
	lights_.push_back(lit);
	return *this;
}

int SceneStyle::GetLightCount() {
	std::lock_guard<std::recursive_mutex> lck(mtx_);
	return (int)lights_.size();
}

Light SceneStyle::GetLightAt(int i) {
	std::lock_guard<std::recursive_mutex> lck(mtx_);
	return lights_.at(i);
}
