#pragma once

#include "Symbolizer.h"
#include "PBRMaterial.h"

namespace geo3dml {

	class LineSymbolizer : public Symbolizer {
	public:
		LineSymbolizer();
		virtual ~LineSymbolizer();

		void SetWidth(float w = 2);
		float GetWidth() const;

		void SetMaterial(const PBRMaterial& m);
		const PBRMaterial& GetMaterial() const;

	private:
		float lineWidth_;
		PBRMaterial material_;
	};
}
