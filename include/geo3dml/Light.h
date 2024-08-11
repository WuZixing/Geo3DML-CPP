// UTF-8编码
#pragma once

#include "Color.h"
#include <string>

namespace geo3dml {

	/// @brief 光源配置。
	class Light {
	public:
		/// @brief 光源的类型。
		enum Type {
			Light_Unknown,	///< 未知类型。
			/// @name 局标的光源类型定义。
			///@{
			Light_Head,		///< 头灯
			Light_Camera,	///< 相机灯
			Light_Scene,	///< 场景等
			///@}
			/// @name 地理信息协会标准的光源类型定义。
			///@{
			Light_DirectionalLight,	///< 定向光源，模拟环境光。
			Light_PointLight,		///< 点光源，模拟各种点状光源。
			Light_SpotLight,		///< 聚光灯，模拟手电筒、探照灯等光源类型。
			///@}
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