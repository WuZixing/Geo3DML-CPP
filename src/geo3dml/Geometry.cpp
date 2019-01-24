#include <geo3dml/Geometry.h>

using namespace geo3dml;

Geometry::Geometry() {
	lodLevel_ = 0;
}

Geometry::~Geometry() {

}

void Geometry::SetName(const std::string& name) {
	g3d_lock_guard lck(mtx_);
	name_ = name;
}

std::string Geometry::GetName() {
	g3d_lock_guard lck(mtx_);
	return name_;
}

void Geometry::SetLODLevel(int l) {
	g3d_lock_guard lck(mtx_);
	lodLevel_ = l;
}

int Geometry::GetLODLevel() {
	g3d_lock_guard lck(mtx_);
	return lodLevel_;
}
