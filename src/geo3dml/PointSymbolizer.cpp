#include <geo3dml/PointSymbolizer.h>

using namespace geo3dml;

PointSymbolizer::PointSymbolizer() {
	pointSize_ = 2;
}

PointSymbolizer::~PointSymbolizer() {

}

void PointSymbolizer::SetSize(float s) {
	pointSize_ = s;
}

float PointSymbolizer::GetSize() const {
	return pointSize_;
}

void PointSymbolizer::SetMaterial(const Material& m) {
	material_ = m;
}

Material PointSymbolizer::GetMaterial() const {
	return material_;
}
