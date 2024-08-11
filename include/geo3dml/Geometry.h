// UTF-8编码
#pragma once

#include "Box3D.h"
#include "Geo3DML.h"
#include "ShapeProperty.h"

namespace geo3dml {

	/// A Geometry object is thread safe.
	class Geometry : public Object {
	public:
		Geometry();
		virtual ~Geometry();

		/// Compute the minimum bounding rectangle of the shape.
		/// @return In case of a null shape which means a geometry without any vertex, it will return an invalid Box3D.
		virtual Box3D GetMinimumBoundingRectangle() const = 0;
		virtual void SetProperty(ShapeProperty* prop, ShapeProperty::SamplingTarget t) = 0;
		virtual ShapeProperty* GetProperty(ShapeProperty::SamplingTarget t) const = 0;
	};
}
