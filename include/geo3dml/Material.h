// UTF-8编码
#pragma once

#include <string>
#include "Color.h"
#include "Texture.h"

namespace geo3dml {
	/// @brief 可视化材质参数。
	/// 地调局标准（简称局标，或v1版标准）与地理信息协会标准（简称协会标准，或v2版标准）使用不同的材质定义。
	/// 两个版本使用完全不同的属性。但从实际效果看，v2版本涵盖了v1版本。
	class Material {
	public:
		Material();
		virtual ~Material();

		/// @brief 基础颜色
		void SetBaseColor(const Color& clr);
		const Color& GetBaseColor() const;

		/// @brief 基础纹理。有纹理时忽略基础颜色参数。
		void SetBaseTexture(const Texture& tex);
		const Texture& GetBaseTexture() const;

		/// 对象发光时的颜色。
		void SetEmissiveColor(const Color& clr);
		const Color& GetEmissiveColor() const;

		/// 对象的法向纹理。
		void SetNormalTexture(const Texture& tex);
		const Texture& GetNormalTexture() const;

		/// 环境光遮蔽纹理。仅使用其R通道的值。
		void SetOcclusionTexture(const Texture& tex);
		const Texture& GetOcclusionTexture() const;

	private:
		Color baseColor_;		///< 对象自身的颜色。
		Texture baseTexture_;	///< 对象自身纹理。有纹理时忽略baseColor_。
		Color emissiveColor_;	///< 若对象发光，指定其发光的颜色。
		Texture normalTexture_;	///< 对象的法向纹理。使用其RGB通道的值。
		Texture occlusionTexture_;	///< 环境光遮蔽纹理。仅使用其R通道的值。
	};
}
