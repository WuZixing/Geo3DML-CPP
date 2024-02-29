#pragma once

#include "LineString.h"

namespace geo3dml {

	class MultiLineString : public Geometry {
	public:
		MultiLineString();
		virtual ~MultiLineString();

	public:
		/// Append a LineString into the set.
		/// @param line The LineString to be appended. The line object should be destroyed by the caller.
		/// @return The index of the new LineString.
		virtual int AddLineString(const LineString* line) = 0;
		virtual int GetLineStringCount() const = 0;
		virtual int GetVertexCountOfLineString(int lineIndex) const = 0;
		virtual void GetVertexOfLineString(int lineIndex, int vertexIndex, double& x, double& y, double& z) const = 0;
	};
}