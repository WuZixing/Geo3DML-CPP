#pragma once

#include "Geometry.h"

namespace geo3dml {

	class Point : public Geometry {
	public:
		Point();
		virtual ~Point();

	public:
		virtual void SetPosition(double x, double y, double z) = 0;
		virtual void GetPosition(double& x, double& y, double& z) = 0;
	};
}
