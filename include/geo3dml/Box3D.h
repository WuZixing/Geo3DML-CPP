#pragma once

#include "Point3D.h"

namespace geo3dml {

	struct Box3D {
		Box3D() : min(0, 0, 0), max(-1, -1, -1) { };
		Box3D(const Point3D& min, const Point3D& max) {
			this->min = min;
			this->max = max;
		};

		bool IsEmpty() const {
			return min.x > max.x;
		};

		/// Extent in X, Y, and Z axies.
		Point3D Extent() const {
			return Point3D(max.x - min.x, max.y - min.y, max.z - min.z);
		}

		Point3D min, max;
	};
}