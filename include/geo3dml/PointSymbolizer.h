#pragma once

#include "Symbolizer.h"
#include "PBRMaterial.h"

namespace geo3dml {

	class PointSymbolizer : public Symbolizer {
	public:
		PointSymbolizer();
		virtual ~PointSymbolizer();

		void SetSize(float s = 2);
		float GetSize() const;

		void SetMaterial(const PBRMaterial& m);
		const PBRMaterial& GetMaterial() const;

	private:
		float pointSize_;
		PBRMaterial material_;
	};
}
