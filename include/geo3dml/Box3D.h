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
		
		bool IsValid() const {
			return !IsEmpty();
		}

		Box3D& UnionWith(const Box3D& box) {
			if (box.IsEmpty()) {
				return *this;
			}
			if (IsEmpty()) {
				min = box.min;
				max = box.max;
				return *this;
			}
			if (min.x > box.min.x) {
				min.x = box.min.x;
			}
			if (min.y > box.min.y) {
				min.y = box.min.y;
			}
			if (min.z > box.min.z) {
				min.z = box.min.z;
			}
			if (max.x < box.max.x) {
				max.x = box.max.x;
			}
			if (max.y < box.max.y) {
				max.y = box.max.y;
			}
			if (max.z < box.max.z) {
				max.z = box.max.z;
			}
			return *this;
		}

		/// Extent in X, Y, and Z axies.
		Point3D Extent() const {
			return Point3D(max.x - min.x, max.y - min.y, max.z - min.z);
		}

		Point3D min, max;
	};
}