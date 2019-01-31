#include <g3dxml/XMLMaterialReader.h>

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
		if (nodeType == XML_READER_TYPE_END_ELEMENT && _stricmp(localName, Element.c_str()) == 0) {
			break;
		} else if (nodeType == XML_READER_TYPE_ELEMENT) {
			if (_stricmp(localName, Element_AmbientIntensity.c_str()) == 0) {
				std::string ambient;
				if (!XMLReaderHelper::TextNode(reader, Element_AmbientIntensity, ambient)) {
					SetStatus(false, ambient);
					break;
				}
				toMaterial.SetAmbientIntensity(strtod(ambient.c_str(), NULL));
			} else if (_stricmp(localName, Element_DiffuseColor.c_str()) == 0) {
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
			} else if (_stricmp(localName, Element_EmissiveColor.c_str()) == 0) {
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
			} else if (_stricmp(localName, Element_Shininess.c_str()) == 0) {
				std::string shininess;
				if (!XMLReaderHelper::TextNode(reader, Element_Shininess, shininess)) {
					SetStatus(false, shininess);
					break;
				}
				toMaterial.SetShininess(strtod(shininess.c_str(), NULL));
			} else if (_stricmp(localName, Element_SpecularColor.c_str()) == 0) {
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
			} else if (_stricmp(localName, Element_Transparency.c_str()) == 0) {
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
