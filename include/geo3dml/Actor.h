#pragma once

#include "Feature.h"
#include "Symbolizer.h"

namespace geo3dml {
	/// A rendered object in a layer.
	class Actor {
	public:
		Actor();
		virtual ~Actor();

		void SetName(const std::string& name);
		std::string GetName() const;

		virtual void BindGeometry(Feature* feature, Geometry* geo, Symbolizer* sym) = 0;
		virtual Feature* GetBindingFeature() const = 0;
		virtual Geometry* GetBindingGeometry() const = 0;

		virtual Symbolizer* GetSymbozier() = 0;

	private:
		std::string name_;
	};
}
