#pragma once

#include "Geo3DML.h"
#include "ShapeProperty.h"

namespace geo3dml {

	/// A Geometry object is thread safe.
	class Geometry : public Object {
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

		/// Compute the minimum bounding rectangle of the shape.
		/// @param minX Output the minimum X coordinate.
		/// @param minY Output the minimum Y coordinate.
		/// @param minZ Output the minimum X coordinate.
		/// @param maxX Output the maximum X coordinate.
		/// @param maxY Output the maximum Y coordinate.
		/// @param maxZ Output the maximum Z coordinate.
		/// @return In case of a null shape which means a geometry without any vertex, it will return false.
		virtual bool GetMinimumBoundingRectangle(double& minX, double& minY, double& minZ, double& maxX, double& maxY, double& maxZ) = 0;
		virtual void SetProperty(ShapeProperty* prop, ShapeProperty::SamplingTarget t) = 0;
		virtual ShapeProperty* GetProperty(ShapeProperty::SamplingTarget t) = 0;

	private:
		std::string name_;
		int lodLevel_;
	};
}
