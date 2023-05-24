#pragma once

#include "Style.h"

namespace geo3dml {

	class FeatureTypeStyle : public Style {
	public:
		FeatureTypeStyle();
		virtual ~FeatureTypeStyle();

	protected:
		virtual void Reserved() override {};
	};
}
