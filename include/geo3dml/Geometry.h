#pragma once

#include "Shape.h"
#include <mutex>

namespace geo3dml {

	/// A Geometry object is thread safe.
	class Geometry {
	public:
		Geometry();
		virtual ~Geometry();

		//@{
		void SetName(const std::string& name);
		std::string GetName();
		//@}

		//@{
		void SetLODLevel(int l);
		int GetLODLevel();
		//@}

		//@{
		/// Set or replace the shape object bound by this geometry.
		/// @param shape the Shape object binding with this geometry. It will be deallocated by this Geometry object unless it was replaced by another shape object.
		/// @return the replaced shape if there was a bound Shape object. The returned object should be deallocated by the caller.
		Shape* SetShape(Shape* shape);
		Shape* GetShape();
		//@}

		/// Compute bounding box of the geometry.
		/// @param minX Output the minimum X coordinate.
		/// @param minY Output the minimum Y coordinate.
		/// @param minZ Output the minimum X coordinate.
		/// @param maxX Output the maximum X coordinate.
		/// @param maxY Output the maximum Y coordinate.
		/// @param maxZ Output the maximum Z coordinate.
		/// @return In case of a geometry without a valid shape, it will return false.
		bool GetBoundingBox(double& minX, double& minY, double& minZ, double& maxX, double& maxY, double& maxZ);

	private:
		std::string name_;
		int lodLevel_;
		Shape* shape_;
		std::mutex mtx_;
	};
}
