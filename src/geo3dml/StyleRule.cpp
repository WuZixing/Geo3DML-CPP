#include <geo3dml/StyleRule.h>

using namespace geo3dml;

Field StyleRule::GetFieldOfFeatureID() {
	return Field().Name("gml:id").DataType(Field::Text);
}

StyleRule::StyleRule() {
	symbolizer_ = NULL;
}

StyleRule::~StyleRule() {
	if (symbolizer_ != NULL) {
		delete symbolizer_;
	}
}

void StyleRule::SetSymbolizer(Symbolizer* sym) {
	symbolizer_ = sym;
}

Symbolizer* StyleRule::GetSymbolizer() const {
	return symbolizer_;
}

bool StyleRule::DoesFeatureMatch(Feature* feature) const {
	// match any feature.
	return true;
}
