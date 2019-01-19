#include <geo3dml/StyleRule.h>

using namespace geo3dml;

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

Symbolizer*StyleRule::GetSymbolizer() const {
	return symbolizer_;
}
