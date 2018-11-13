#include <geo3dml/Geometry.h>

using namespace geo3dml;

Geometry::Geometry() {
	lodLevel_ = 0;
	shape_ = NULL;
}

Geometry::~Geometry() {
	if (shape_ != NULL) {
		delete shape_;
		shape_ = NULL;
	}
}

void Geometry::SetName(const std::string& name) {
	std::lock_guard<std::mutex> lck(mtx_);
	name_ = name;
}

std::string Geometry::GetName() {
	std::lock_guard<std::mutex> lck(mtx_);
	return name_;
}

void Geometry::SetLODLevel(int l) {
	std::lock_guard<std::mutex> lck(mtx_);
	lodLevel_ = l;
}

int Geometry::GetLODLevel() {
	std::lock_guard<std::mutex> lck(mtx_);
	return lodLevel_;
}

Shape* Geometry::SetShape(Shape* shape) {
	std::lock_guard<std::mutex> lck(mtx_);
	Shape* oldShape = shape_;
	shape_ = shape;
	return oldShape;
}

Shape* Geometry::GetShape() {
	std::lock_guard<std::mutex> lck(mtx_);
	return shape_;
}

bool Geometry::GetBoundingBox(double& minX, double& minY, double& minZ, double& maxX, double& maxY, double& maxZ) {
	std::lock_guard<std::mutex> lck(mtx_);
	if (shape_ != NULL) {
		return shape_->GetBoundingBox(minX, minY, minZ, maxX, maxY, maxZ);
	} else {
		return false;
	}
}
