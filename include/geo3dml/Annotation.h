#pragma once

#include "MultiPoint.h"

namespace geo3dml {

	/// @brief An annotation object is a multi-point with a text label for each point.
	class Annotation : public MultiPoint {
	public:
		Annotation();
		virtual ~Annotation();

		virtual void SetLabelOfPointAt(int i, const std::string& s) = 0;
		virtual std::string GetLabelOfPointAt(int i) = 0;
	};
}
