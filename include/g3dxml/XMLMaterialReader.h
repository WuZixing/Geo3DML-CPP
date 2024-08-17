// UTF-8编码
#pragma once

#include <g3dxml/XMLReaderHelper.h>
#include <g3dxml/XMLIO.h>

namespace g3dxml {
	/// @brief PBR材质参数读取方法。
	class XMLMaterialReader : public XMLIO {
	public:
		/// Name of the basic material element.
		static const std::string Element;
		/// Name of the PBR material element.
		static const std::string Element_PBRMaterial;

	public:
		/// Constructor.
		XMLMaterialReader();
		virtual ~XMLMaterialReader();

		/// @brief 从XML数据据中读取材质参数。
		/// @param reader		XML数据读取工具。
		/// @param materialTag	当前要读取的材质参数的XML元素标签名字，可为"Material"或"PBRMaterial"。
		/// @param toMaterial	输出材质参数。
		/// @return 读取成功时返回true，否则返回false。
		bool ReadMaterial(xmlTextReaderPtr reader, const std::string& materialTag, geo3dml::PBRMaterial& toMaterial);

	private:
		bool ReadTexture(xmlTextReaderPtr reader, const std::string& texElemTag, geo3dml::Texture& texture);

	private:
		const std::string Element_DiffuseColor;
		const std::string Element_Texture;
		const std::string Element_BaseColor;
		const std::string Element_EmissiveColor;
		const std::string Element_BaseTexture;
		const std::string Element_NormalTexture;
		const std::string Element_OcclusionTexture;
		const std::string Element_Metallic;
		const std::string Element_Roughness;
		const std::string Element_SpecularColor;
		const std::string Element_IndexOfRefraction;
	};
}
