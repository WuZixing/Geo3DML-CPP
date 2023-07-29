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

		//@{
		void SetName(const std::string& name);
		const std::string& GetName() const;
		//@}

		//@{
		void SetLODLevel(int l);
		int GetLODLevel() const;
		//@}

		/// Compute the minimum bounding rectangle of the shape.
		/// @return In case of a null shape which means a geometry without any vertex, it will return an invalid Box3D.
		virtual Box3D GetMinimumBoundingRectangle() const = 0;
		virtual void SetProperty(ShapeProperty* prop, ShapeProperty::SamplingTarget t) = 0;
		virtual ShapeProperty* GetProperty(ShapeProperty::SamplingTarget t) const = 0;

	private:
		std::string name_;
		int lodLevel_;
	};
}
