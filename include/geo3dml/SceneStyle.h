#pragma once

#include "Light.h"
#include <vector>
#include <mutex>

namespace geo3dml {

	/// SceneStyle is thread safe.
	class SceneStyle {
	public:
		SceneStyle();
		virtual ~SceneStyle();

		//@{
		SceneStyle& SetBackgroundColor(const Color& c);
		Color GetBackgroundColor() const;
		//@}

		/// @name Lights, 8 at most.
		//@{
		SceneStyle& AddLight(const Light& lit);
		int GetLightCount() const;
		Light GetLightAt(int i) const;
		//@}

	private:
		Color color_;
		std::vector<Light> lights_;
		std::recursive_mutex mtx_;
	};
}
