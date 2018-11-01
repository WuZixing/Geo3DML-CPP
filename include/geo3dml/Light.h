#pragma once

#include "Color.h"
#include <string>

namespace geo3dml {

	class Light {
	public:
		enum Type {
			Light_Head,
			Light_Camera,
			Light_Scene
		};
		static Type NameToLightType(const std::string& name);

	public:
		Light();
		virtual ~Light();

		Light& Switch(bool on);
		bool IsOn() const;

		Light& SetType(Type t);
		Type GetType() const;

		Light& SetPosition(double x, double y, double z);
		void GetPosition(double& x, double& y, double& z);
		Light& SetFocalPosition(double x, double y, double z);
		void GetFocalPosition(double& x, double& y, double& z);

		Light& SetIntensity(double i);
		double GetIntensity() const;

		Light& SetAmbientColor(const Color& c);
		Color GetAmbientColor() const;
		Light& SetDiffuseColor(const Color& c);
		Color GetDiffuseColor() const;
		Light& SetSpecularColor(const Color& c);
		Color GetSpecularColor() const;

	private:
		bool isOn_;
		Type lightType_;
		double position_[3];
		double focalPosition_[3];
		double intensity_;	///< Strength of the light.
		Color ambientColor_;
		Color diffuseColor_;
		Color specularColor_;
	};
}