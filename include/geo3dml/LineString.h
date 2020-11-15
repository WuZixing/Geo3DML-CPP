#pragma once

#include "Geometry.h"

namespace geo3dml {

	class LineString : public Geometry {
	public:
		LineString();
		virtual ~LineString();

	public:
		virtual void AddVertex(double x, double y, double z) = 0;
		virtual int GetVertexCount() const = 0;
		virtual void GetVertexAt(int i, double& x, double& y, double& z) const = 0;
	};
}
