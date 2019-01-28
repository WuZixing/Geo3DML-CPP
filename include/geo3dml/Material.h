#pragma once

#include "Color.h"

namespace geo3dml {

	class Material {
	public:
		Material();
		virtual ~Material();

		/// @name Ambient intensity: [0, 1.0]
		//@{
		void SetAmbientIntensity(double d = 0.2);
		double GetAmbientIntensity() const;
		//@}

		/// @name Shininess: [0, 1.0]
		//@{
		void SetShininess(double d = 0.2);
		double GetShininess() const;
		//@}

		/// @name Transparency: [0, 1.0]
		//@{
		void SetTransparency(double d = 0);
		double GetTransparency() const;
		//@}

		/// @name Colors
		//@{
		void SetDiffuseColor(const Color& clr);
		Color GetDiffuseColor() const;
		void SetEmissiveColor(const Color& clr);
		Color GetEmissiveColor() const;
		void SetSpecularColor(const Color& clr);
		Color GetSpecularColor() const;
		//@}

	private:
		double ambientIntensity_, shininess_, transparency_;
		Color diffuseColor_, emissiveColor_, specularColor_;
	};
}
