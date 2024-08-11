// UTF-8编码
#pragma once

#include <g3dxml/XMLReaderHelper.h>
#include <g3dxml/XMLIO.h>

namespace g3dxml {
	/// @brief 基础材质参数读取方法。
	class XMLMaterialReader : public XMLIO {
	public:
		/// Name of the geometry element.
		static const std::string Element;

	public:
		/// Constructor.
		XMLMaterialReader();
		virtual ~XMLMaterialReader();

		bool ReadMaterial(xmlTextReaderPtr reader, geo3dml::Material& toMaterial);

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
	};

	/// @brief PBR材质参数读取方法。
	class XMLPBRMaterialReader : public XMLIO {
	public:
		static const std::string Element;
	};
}
