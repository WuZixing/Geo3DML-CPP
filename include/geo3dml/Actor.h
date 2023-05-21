#pragma once

#include "Feature.h"
#include "Symbolizer.h"

namespace geo3dml {
	/// A rendered object in a layer.
	class Actor : public Object {
	public:
		Actor();
		virtual ~Actor();

		void SetName(const std::string& name);
		std::string GetName() const;

		virtual void BindGeometry(Feature* feature, Geometry* geo, Symbolizer* sym) = 0;
		virtual Feature* GetBindingFeature() const = 0;
		virtual Geometry* GetBindingGeometry() const = 0;

		virtual bool IsVisible() const = 0;
		virtual void SetVisible(bool show) = 0;

		/// Make a Symbolizer object which represents render parameters of the actor.
		/// @return The returned Symbolizer object should be deallocated by the caller.
		virtual Symbolizer* MakeSymbozier() const = 0;

		/// Compute the minimum bounding rectangle of the feature class.
		/// @return In case of an empty feature class, it will return an invalid Box3D.
		Box3D GetMinimumBoundingRectangle() const;

	private:
		std::string name_;
	};
}
