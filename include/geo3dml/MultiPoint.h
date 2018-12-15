#pragma once

#include "Shape.h"

namespace geo3dml {

	class MultiPoint : public Shape {
	public:
		MultiPoint();
		virtual ~MultiPoint();

	public:
		virtual void AddPoint(double x, double y, double z) = 0;
		virtual int GetPointCount() = 0;
		virtual void GetPointAt(int i, double& x, double& y, double& z) = 0;
	};
}
