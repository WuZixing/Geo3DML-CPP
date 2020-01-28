#include <g3dxml/XMLMaterialReader.h>
#include <geo3dml/Utils.h>

using namespace g3dxml;

std::string XMLMaterialReader::Element = "Material";

XMLMaterialReader::XMLMaterialReader(geo3dml::ObjectFactory* factory) :
	Element_AmbientIntensity("AmbientIntensity"),
	Element_DiffuseColor("DiffuseColor"),
	Element_EmissiveColor("EmissiveColor"),
	Element_Shininess("Shininess"),
	Element_SpecularColor("SpecularColor"),
	Element_Transparency("Transparency") {
	g3dFactory_ = factory;
}

XMLMaterialReader::~XMLMaterialReader() {
	g3dFactory_ = NULL;
}

bool XMLMaterialReader::ReadMaterial(xmlTextReaderPtr reader, geo3dml::Material& toMaterial) {
	int status = xmlTextReaderRead(reader);
	while (status == 1) {
		const char* localName = (const char*)xmlTextReaderConstLocalName(reader);
		int nodeType = xmlTextReaderNodeType(reader);
		if (nodeType == XML_READER_TYPE_END_ELEMENT && geo3dml::IsiEqual(localName, Element)) {
			break;
		} else if (nodeType == XML_READER_TYPE_ELEMENT) {
			if (geo3dml::IsiEqual(localName, Element_AmbientIntensity)) {
				std::string ambient;
				if (!XMLReaderHelper::TextNode(reader, Element_AmbientIntensity, ambient)) {
					SetStatus(false, ambient);
					break;
				}
				toMaterial.SetAmbientIntensity(strtod(ambient.c_str(), NULL));
			} else if (geo3dml::IsiEqual(localName, Element_DiffuseColor)) {
				std::string diffuseColor;
				if (!XMLReaderHelper::TextNode(reader, Element_DiffuseColor, diffuseColor)) {
					SetStatus(false, diffuseColor);
					break;
				}
				char* end = NULL;
				double r = strtod(diffuseColor.c_str(), &end);
				double g = strtod(end, &end);
				double b = strtod(end, NULL);
				toMaterial.SetDiffuseColor(geo3dml::Color(r, g, b));
			} else if (geo3dml::IsiEqual(localName, Element_EmissiveColor)) {
				std::string emissiveColor;
				if (!XMLReaderHelper::TextNode(reader, Element_EmissiveColor, emissiveColor)) {
					SetStatus(false, emissiveColor);
					break;
				}
				char* end = NULL;
				double r = strtod(emissiveColor.c_str(), &end);
				double g = strtod(end, &end);
				double b = strtod(end, NULL);
				toMaterial.SetEmissiveColor(geo3dml::Color(r, g, b));
			} else if (geo3dml::IsiEqual(localName, Element_Shininess)) {
				std::string shininess;
				if (!XMLReaderHelper::TextNode(reader, Element_Shininess, shininess)) {
					SetStatus(false, shininess);
					break;
				}
				toMaterial.SetShininess(strtod(shininess.c_str(), NULL));
			} else if (geo3dml::IsiEqual(localName, Element_SpecularColor)) {
				std::string specularColor;
				if (!XMLReaderHelper::TextNode(reader, Element_SpecularColor, specularColor)) {
					SetStatus(false, specularColor);
					break;
				}
				char* end = NULL;
				double r = strtod(specularColor.c_str(), &end);
				double g = strtod(end, &end);
				double b = strtod(end, NULL);
				toMaterial.SetSpecularColor(geo3dml::Color(r, g, b));
			} else if (geo3dml::IsiEqual(localName, Element_Transparency)) {
				std::string transparency;
				if (!XMLReaderHelper::TextNode(reader, Element_Transparency, transparency)) {
					SetStatus(false, transparency);
					break;
				}
				toMaterial.SetTransparency(strtod(transparency.c_str(), NULL));
			}
		}
		status = xmlTextReaderRead(reader);
	}
	if (status != 1) {
		std::string err = XMLReaderHelper::FormatErrorMessageWithPosition(reader, "missing end element of " + Element);
		SetStatus(false, err);
	}
	return IsOK();
}
