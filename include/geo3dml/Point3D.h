#pragma once

#include "Vector3D.h"

namespace geo3dml {
	
	struct Point3D {
		Point3D(double x = 0, double y = 0, double z = 0) {
			this->x = x;
			this->y = y;
			this->z = z;
		};

		Point3D operator+(const Vector3D& v) const {
			return Point3D(x + v.X(), y + v.Y(), z + v.Z());
		};

		double x, y, z;
	};
}