#pragma once

#include "LineString.h"

namespace geo3dml {

	class MultiLineString : public Geometry {
	public:
		MultiLineString();
		virtual ~MultiLineString();

	public:
		/// Append a new LineString into the set.
		/// @return The index of the new LineString.
		virtual int AddLineString() = 0;
		virtual int GetLineStringCount() const = 0;

		virtual void AddVertexToLineString(int lineIndex, double x, double y, double z) = 0;
		virtual int GetVertexCountOfLineString(int lineIndex) const = 0;
		virtual void GetVertexOfLineString(int lineIndex, int vertexIndex, double& x, double& y, double& z) const = 0;
	};
}