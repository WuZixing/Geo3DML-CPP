#include <geo3dml/Geometry.h>

using namespace geo3dml;

Geometry::Geometry() {
	lodLevel_ = 0;
}

Geometry::~Geometry() {

}

void Geometry::SetName(const std::string& name) {
	name_ = name;
}

const std::string& Geometry::GetName() const {
	return name_;
}

void Geometry::SetLODLevel(int l) {
	lodLevel_ = l;
}

int Geometry::GetLODLevel() const {
	return lodLevel_;
}
