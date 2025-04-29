// UTF-8编码
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

        /// @brief 绑定要素及其关联的几何体和可视化参数。
        /// @param feature	要素。指针所指向的对象由调用者负责管理。
		/// @param geo		关联的几何对象。指针所指向的对象由调用者负责管理。
		/// @param sym		关联的可视化参数。指针所指向的对象由调用者负责管理。
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
