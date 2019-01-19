#pragma once

#include "Symbolizer.h"
#include "Feature.h"

namespace geo3dml {

	class StyleRule {
	public:
		StyleRule();
		virtual ~StyleRule();

		void SetSymbolizer(Symbolizer* sym);
		Symbolizer* GetSymbolizer() const;

		virtual bool DoesFeatureMatch(Feature* feature) = 0;

	private:
		Symbolizer* symbolizer_;
	};
}
