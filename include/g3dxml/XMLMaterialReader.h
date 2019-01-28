#pragma once

#include <g3dxml/XMLReaderHelper.h>
#include <g3dxml/XMLIO.h>

namespace g3dxml {

	class XMLMaterialReader : public XMLIO {
	public:
		/// Name of the geometry element.
		static std::string Element;

	public:
		/// Constructor.
		/// @param factory the factory of Geo3DML objects. The factory object should be deallocated by the caller.
		XMLMaterialReader(geo3dml::ObjectFactory* factory);
		virtual ~XMLMaterialReader();

		bool ReadMaterial(xmlTextReaderPtr reader, geo3dml::Material& toMaterial);

	private:
		const std::string Element_AmbientIntensity;
		const std::string Element_DiffuseColor;
		const std::string Element_EmissiveColor;
		const std::string Element_Shininess;
		const std::string Element_SpecularColor;
		const std::string Element_Transparency;

	private:
		geo3dml::ObjectFactory* g3dFactory_;
	};
}
