// UTF-8编码
#include <geo3dml/LineSymbolizer.h>

using namespace geo3dml;

LineSymbolizer::LineSymbolizer() {
	lineWidth_ = 2;
}

LineSymbolizer::~LineSymbolizer() {

}

Symbolizer* LineSymbolizer::Clone() const {
    LineSymbolizer* sym = new LineSymbolizer();
    sym->lineWidth_ = lineWidth_;
    sym->material_ = material_;
    return sym;
}

void LineSymbolizer::SetWidth(float w) {
	lineWidth_ = w;
}

float LineSymbolizer::GetWidth() const {
	return lineWidth_;
}

void LineSymbolizer::SetMaterial(const PBRMaterial& m) {
	material_ = m;
}

const PBRMaterial& LineSymbolizer::GetMaterial() const {
	return material_;
}
