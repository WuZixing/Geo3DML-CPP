#pragma once

#include "Geo3DStyle.h"

namespace geo3dml {

	class FeatureTypeStyle : public Geo3DStyle {
	public:
		FeatureTypeStyle();
		virtual ~FeatureTypeStyle();

	protected:
		virtual void Reserved() {};
	};
}
