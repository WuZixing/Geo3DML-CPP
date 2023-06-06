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
	Element_Transparency("Transparency"),
	Element_Texture("Texture") {
	g3dFactory_ = factory;
}

XMLMaterialReader::~XMLMaterialReader() {
	g3dFactory_ = nullptr;
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
				toMaterial.SetAmbientIntensity(strtod(ambient.c_str(), nullptr));
			} else if (geo3dml::IsiEqual(localName, Element_DiffuseColor)) {
				std::string diffuseColor;
				if (!XMLReaderHelper::TextNode(reader, Element_DiffuseColor, diffuseColor)) {
					SetStatus(false, diffuseColor);
					break;
				}
				char* end = nullptr;
				double r = strtod(diffuseColor.c_str(), &end);
				double g = strtod(end, &end);
				double b = strtod(end, nullptr);
				toMaterial.SetDiffuseColor(geo3dml::Color(r, g, b));
			} else if (geo3dml::IsiEqual(localName, Element_EmissiveColor)) {
				std::string emissiveColor;
				if (!XMLReaderHelper::TextNode(reader, Element_EmissiveColor, emissiveColor)) {
					SetStatus(false, emissiveColor);
					break;
				}
				char* end = nullptr;
				double r = strtod(emissiveColor.c_str(), &end);
				double g = strtod(end, &end);
				double b = strtod(end, nullptr);
				toMaterial.SetEmissiveColor(geo3dml::Color(r, g, b));
			} else if (geo3dml::IsiEqual(localName, Element_Shininess)) {
				std::string shininess;
				if (!XMLReaderHelper::TextNode(reader, Element_Shininess, shininess)) {
					SetStatus(false, shininess);
					break;
				}
				toMaterial.SetShininess(strtod(shininess.c_str(), nullptr));
			} else if (geo3dml::IsiEqual(localName, Element_SpecularColor)) {
				std::string specularColor;
				if (!XMLReaderHelper::TextNode(reader, Element_SpecularColor, specularColor)) {
					SetStatus(false, specularColor);
					break;
				}
				char* end = nullptr;
				double r = strtod(specularColor.c_str(), &end);
				double g = strtod(end, &end);
				double b = strtod(end, nullptr);
				toMaterial.SetSpecularColor(geo3dml::Color(r, g, b));
			} else if (geo3dml::IsiEqual(localName, Element_Transparency)) {
				std::string transparency;
				if (!XMLReaderHelper::TextNode(reader, Element_Transparency, transparency)) {
					SetStatus(false, transparency);
					break;
				}
				toMaterial.SetTransparency(strtod(transparency.c_str(), nullptr));
			} else if (geo3dml::IsiEqual(localName, Element_Texture)) {
				geo3dml::Texture tex;
				if (ReadTexture(reader, tex)) {
					toMaterial.SetTexture(tex);
				} else {
					break;
				}
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

bool XMLMaterialReader::ReadTexture(xmlTextReaderPtr reader, geo3dml::Texture& texture) {
	int status = xmlTextReaderRead(reader);
	while (status == 1) {
		const char* localName = (const char*)xmlTextReaderConstLocalName(reader);
		int nodeType = xmlTextReaderNodeType(reader);
		if (nodeType == XML_READER_TYPE_END_ELEMENT && geo3dml::IsiEqual(localName, Element_Texture)) {
			break;
		} else if (nodeType == XML_READER_TYPE_ELEMENT) {
			if (geo3dml::IsiEqual(localName, "ImageURI")) {
				std::string imageURI;
				if (XMLReaderHelper::TextNode(reader, "ImageURI", imageURI)) {
					if (XMLReaderHelper::IsRelativePath(imageURI)) {
						xmlDocPtr doc = xmlTextReaderCurrentDoc(reader);
						if (doc != nullptr) {
							char* dir = xmlParserGetDirectory((const char*)doc->URL);
							char sep = '/';
#if defined(WIN32) && !defined(__CYGWIN__)
							sep = '\\';
#endif
							texture.SetImageURI(std::string(dir) + sep + imageURI);
							xmlFree(dir);
						}
					} else {
						texture.SetImageURI(imageURI);
					}
				} else {
					SetStatus(false, imageURI);
					break;
				}
			} else if (geo3dml::IsiEqual(localName, "MimeType")) {
				std::string mime;
				if (XMLReaderHelper::TextNode(reader, "MimeType", mime)) {
					texture.SetImageMime(mime);
				} else {
					SetStatus(false, mime);
					break;
				}
			} else if (geo3dml::IsiEqual(localName, "WrapMode")) {
				std::string wrapMode;
				if (XMLReaderHelper::TextNode(reader, "WrapMode", wrapMode)) {
					if (geo3dml::IsiEqual(wrapMode, "None")) {
						texture.SetWrapMode(geo3dml::Texture::WrapMode::Default);
					} else if (geo3dml::IsiEqual(wrapMode, "Wrap")) {
						texture.SetWrapMode(geo3dml::Texture::WrapMode::Repeat);
					} else if (geo3dml::IsiEqual(wrapMode, "Mirror")) {
						texture.SetWrapMode(geo3dml::Texture::WrapMode::MirrorRepeat);
					} else if (geo3dml::IsiEqual(wrapMode, "Clamp")) {
						texture.SetWrapMode(geo3dml::Texture::WrapMode::ClampToEdge);
					} else if (geo3dml::IsiEqual(wrapMode, "Border")) {
						texture.SetWrapMode(geo3dml::Texture::WrapMode::ClampToBorder);
					}
				} else {
					SetStatus(false, wrapMode);
					break;
				}
			} else if (geo3dml::IsiEqual(localName, "BorderColor")) {
				std::string borderColor;
				if (XMLReaderHelper::TextNode(reader, "BorderColor", borderColor)) {
					char* end = nullptr;
					double r = strtod(borderColor.c_str(), &end);
					double g = strtod(end, &end);
					double b = strtod(end, &end);
					double a = strtod(end, nullptr);
					texture.SetBorderColor(geo3dml::Color(r, g, b, a));
				} else {
					SetStatus(false, borderColor);
					break;
				}
			}
		}
		status = xmlTextReaderRead(reader);
	}
	if (status != 1) {
		std::string err = XMLReaderHelper::FormatErrorMessageWithPosition(reader, "missing end element of " + Element_Texture);
		SetStatus(false, err);
	}
	return IsOK();
}
