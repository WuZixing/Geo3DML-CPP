#include <geo3dml/LineSymbolizer.h>

using namespace geo3dml;

LineSymbolizer::LineSymbolizer() {
	lineWidth_ = 2;
}

LineSymbolizer::~LineSymbolizer() {

}

void LineSymbolizer::SetWidth(float w) {
	lineWidth_ = w;
}

float LineSymbolizer::GetWidth() const {
	return lineWidth_;
}

void LineSymbolizer::SetMaterial(const Material& m) {
	material_ = m;
}

Material LineSymbolizer::GetMaterial() const {
	return material_;
}
