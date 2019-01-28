#pragma once

#include "Symbolizer.h"
#include "Feature.h"

namespace geo3dml {

	class StyleRule {
	public:
		/// Make the field definition for the feature ID property.
		static Field GetFieldOfFeatureID();

	public:
		StyleRule();
		virtual ~StyleRule();

		void SetSymbolizer(Symbolizer* sym);
		Symbolizer* GetSymbolizer() const;

		virtual bool DoesFeatureMatch(Feature* feature);

	private:
		Symbolizer* symbolizer_;
	};
}
