#pragma once

#include "LineString.h"

namespace geo3dml {

	class MultiLineString : public Geometry {
	public:
		MultiLineString();
		virtual ~MultiLineString();

	public:
		virtual void AddLineString(LineString* line) = 0;
		virtual int GetLineStringCount() const = 0;
		virtual LineString* GetLineStringAt(int i) const = 0;
	};
}