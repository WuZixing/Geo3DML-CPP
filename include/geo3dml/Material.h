#pragma once

#include "Color.h"

namespace geo3dml {

	class Material {
	public:
		Material();
		virtual ~Material();

		/// @name Ambient intensity
		//@{
		virtual void SetAmbientIntensity(double d = 0.2);
		virtual double GetAmbientIntensity() const;
		//@}

		/// @name Shininess
		//@{
		virtual void SetShininess(double d = 0.2);
		virtual double GetShininess() const;
		//@}

		/// @name Transparency
		//@{
		virtual void SetTransparency(double d = 0);
		virtual double GetTransparency() const;
		//@}

		/// @name Colors
		//@{
		virtual void SetDiffuseColor(const Color& clr);
		virtual Color GetDiffuseColor() const;
		virtual void SetEmissiveColor(const Color& clr);
		virtual Color GetEmissiveColor() const;
		virtual void SetSpecularColor(const Color& clr);
		virtual Color GetSpecularColor() const;
		//@}

	private:
		double ambientIntensity_, shininess_, transparency_;
		Color diffuseColor_, emissiveColor_, specularColor_;
	};
}
