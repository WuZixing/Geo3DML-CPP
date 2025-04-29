// UTF-8编码
#pragma once

#include "Symbolizer.h"
#include "PBRMaterial.h"

namespace geo3dml {

	class GeoDiscreteCoverageSymbolizer : public Symbolizer {
	public:
		GeoDiscreteCoverageSymbolizer();
		virtual ~GeoDiscreteCoverageSymbolizer();

		///@name 实现父类定义的接口。
		///@{
		virtual Symbolizer* Clone() const override;
		///@}
	};
}
