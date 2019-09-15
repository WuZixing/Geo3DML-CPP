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
		std::string GetName();

		virtual void BindGeometry(Feature* feature, Geometry* geo, Symbolizer* sym) = 0;
		virtual Feature* GetBindingFeature() = 0;
		virtual Geometry* GetBindingGeometry() = 0;

		virtual bool IsVisible() = 0;
		virtual void SetVisible(bool show) = 0;

		/// Make a Symbolizer object which represents render parameters of the actor.
		/// @return The returned Symbolizer object should be deallocated by the caller.
		virtual Symbolizer* MakeSymbozier() = 0;

	private:
		std::string name_;
	};
}
