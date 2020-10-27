#include <geo3dml/Actor.h>

using namespace geo3dml;

Actor::Actor() {

}

Actor::~Actor() {

}

void Actor::SetName(const std::string& name) {
	g3d_lock_guard lck(mtx_);
	name_ = name;
}

std::string Actor::GetName() {
	g3d_lock_guard lck(mtx_);
	return name_;
}

bool Actor::GetMinimumBoundingRectangle(double& minX, double& minY, double& minZ, double& maxX, double& maxY, double& maxZ) {
	Geometry* geo = GetBindingGeometry();
	if (geo != NULL) {
		return geo->GetMinimumBoundingRectangle(minX, minY, minZ, maxX, maxY, maxZ);
	} else {
		return false;
	}
}