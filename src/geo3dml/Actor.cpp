#include <geo3dml/Actor.h>

using namespace geo3dml;

Actor::Actor() {

}

Actor::~Actor() {

}

void Actor::SetName(const std::string& name) {
	name_ = name;
}

std::string Actor::GetName() const {
	return name_;
}

Box3D Actor::GetMinimumBoundingRectangle() const {
	Box3D box;
	Geometry* geo = GetBindingGeometry();
	if (geo != nullptr) {
		box = geo->GetMinimumBoundingRectangle();
	}
	return box;
}