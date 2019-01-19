#pragma once

#include "Symbolizer.h"
#include "Material.h"

namespace geo3dml {

	class PointSymbolizer : public Symbolizer {
	public:
		PointSymbolizer();
		virtual ~PointSymbolizer();

		virtual void SetSize(float s = 2);
		virtual float GetSize() const;

		virtual void SetMaterial(const Material& m);
		virtual Material GetMaterial() const;

	private:
		float pointSize_;
		Material material_;
	};
}
