#pragma once

#include "Geometry.h"

namespace geo3dml {

	struct Point3D {
		Point3D(double x = 0, double y = 0, double z = 0) {
			this->x = x;
			this->y = y;
			this->z = z;
		};

		double x, y, z;
	};

	class Point : public Geometry {
	public:
		Point();
		virtual ~Point();

	public:
		virtual void SetPosition(double x, double y, double z) = 0;
		virtual void GetPosition(double& x, double& y, double& z) = 0;
	};
}
