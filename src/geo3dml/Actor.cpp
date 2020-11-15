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

bool Actor::GetMinimumBoundingRectangle(double& minX, double& minY, double& minZ, double& maxX, double& maxY, double& maxZ) const {
	Geometry* geo = GetBindingGeometry();
	if (geo != NULL) {
		return geo->GetMinimumBoundingRectangle(minX, minY, minZ, maxX, maxY, maxZ);
	} else {
		return false;
	}
}