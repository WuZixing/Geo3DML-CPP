#pragma once

#include "Symbolizer.h"
#include "Material.h"

namespace geo3dml {

	class LineSymbolizer : public Symbolizer {
	public:
		LineSymbolizer();
		virtual ~LineSymbolizer();

		virtual void SetWidth(float w = 2);
		virtual float GetWidth() const;

		virtual void SetMaterial(const Material& m);
		virtual Material GetMaterial() const;

	private:
		float lineWidth_;
		Material material_;
	};
}
