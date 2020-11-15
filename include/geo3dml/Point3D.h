#pragma once

namespace geo3dml {
	
	struct Point3D {
		Point3D(double x = 0, double y = 0, double z = 0) {
			this->x = x;
			this->y = y;
			this->z = z;
		};

		double x, y, z;
	};
}