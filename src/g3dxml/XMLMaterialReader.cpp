#include <g3dxml/XMLMaterialReader.h>
#include <geo3dml/Utils.h>

using namespace g3dxml;

const std::string XMLMaterialReader::Element = "Material";

XMLMaterialReader::XMLMaterialReader() :
	Element_DiffuseColor("DiffuseColor"),
	Element_Texture("Texture"),
	Element_BaseColor("BaseColor"),
	Element_EmissiveColor("EmissiveColor"),
	Element_BaseTexture("BaseTexture"),
	Element_NormalTexture("NormalTexture"),
	Element_OcclusionTexture("OcclusionTexture") {
}

XMLMaterialReader::~XMLMaterialReader() {
}

bool XMLMaterialReader::ReadMaterial(xmlTextReaderPtr reader, geo3dml::Material& toMaterial) {
	int status = xmlTextReaderRead(reader);
	while (status == 1) {
		const char* localName = (const char*)xmlTextReaderConstLocalName(reader);
		int nodeType = xmlTextReaderNodeType(reader);
		if (nodeType == XML_READER_TYPE_END_ELEMENT && geo3dml::IsiEqual(localName, Element)) {
			break;
		} else if (nodeType == XML_READER_TYPE_ELEMENT) {
			if (geo3dml::IsiEqual(localName, Element_DiffuseColor)) {
				std::string diffuseColor;
				if (!XMLReaderHelper::TextNode(reader, Element_DiffuseColor, diffuseColor)) {
					SetStatus(false, diffuseColor);
					break;
				}
				char* end = nullptr;
				double r = strtod(diffuseColor.c_str(), &end);
				double g = strtod(end, &end);
				double b = strtod(end, nullptr);
				toMaterial.SetBaseColor(geo3dml::Color(r, g, b));
			} else if (geo3dml::IsiEqual(localName, Element_BaseColor)) {
				std::string baseColor;
				if (!XMLReaderHelper::TextNode(reader, Element_BaseColor, baseColor)) {
					SetStatus(false, baseColor);
					break;
				}
				char* end = nullptr;
				double r = strtod(baseColor.c_str(), &end);
				double g = strtod(end, &end);
				double b = strtod(end, &end);
				double a = strtod(end, nullptr);
				toMaterial.SetBaseColor(geo3dml::Color(r, g, b, a));
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
			} else if (geo3dml::IsiEqual(localName, Element_BaseTexture)) {
				geo3dml::Texture tex;
				if (ReadTexture(reader, Element_BaseTexture, tex)) {
					toMaterial.SetBaseTexture(tex);
				} else {
					break;
				}
			} else if (geo3dml::IsiEqual(localName, Element_Texture)) {
				geo3dml::Texture tex;
				if (ReadTexture(reader, Element_Texture, tex)) {
					toMaterial.SetBaseTexture(tex);
				} else {
					break;
				}
			} else if (geo3dml::IsiEqual(localName, Element_NormalTexture)) {
				geo3dml::Texture tex;
				if (ReadTexture(reader, Element_NormalTexture, tex)) {
					toMaterial.SetNormalTexture(tex);
				} else {
					break;
				}
			} else if (geo3dml::IsiEqual(localName, Element_OcclusionTexture)) {
				geo3dml::Texture tex;
				if (ReadTexture(reader, Element_OcclusionTexture, tex)) {
					toMaterial.SetOcclusionTexture(tex);
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

bool XMLMaterialReader::ReadTexture(xmlTextReaderPtr reader, const std::string& texElemTag, geo3dml::Texture& texture) {
	geo3dml::GBSymbol gbSymbol;
	int status = xmlTextReaderRead(reader);
	while (status == 1) {
		const char* localName = (const char*)xmlTextReaderConstLocalName(reader);
		int nodeType = xmlTextReaderNodeType(reader);
		if (nodeType == XML_READER_TYPE_END_ELEMENT && geo3dml::IsiEqual(localName, texElemTag)) {
			break;
		} else if (nodeType == XML_READER_TYPE_ELEMENT) {
			if (geo3dml::IsiEqual(localName, "ImageURI") || geo3dml::IsiEqual(localName, "URI")) {
				std::string imageURI;
				if (XMLReaderHelper::TextNode(reader, localName, imageURI)) {
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
				if (XMLReaderHelper::TextNode(reader, localName, mime)) {
					texture.SetImageMime(mime);
				} else {
					SetStatus(false, mime);
					break;
				}
			} else if (geo3dml::IsiEqual(localName, "WrapMode")) {
				std::string wrapMode;
				if (XMLReaderHelper::TextNode(reader, localName, wrapMode)) {
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
				std::string color;
				if (XMLReaderHelper::TextNode(reader, localName, color)) {
					char* end = nullptr;
					double r = strtod(color.c_str(), &end);
					double g = strtod(end, &end);
					double b = strtod(end, &end);
					double a = strtod(end, nullptr);
					texture.SetBorderColor(geo3dml::Color(r, g, b, a));
				} else {
					SetStatus(false, color);
					break;
				}
			} else if (geo3dml::IsiEqual(localName, "Code")) {
				std::string gbSymCode;
				if (XMLReaderHelper::TextNode(reader, localName, gbSymCode)) {
					gbSymbol.SetCode(gbSymCode);
				} else {
					SetStatus(false, gbSymCode);
					break;
				}
			} else if (geo3dml::IsiEqual(localName, "Stroke")) {
				std::string color;
				if (XMLReaderHelper::TextNode(reader, localName, color)) {
					char* end = nullptr;
					double r = strtod(color.c_str(), &end);
					double g = strtod(end, &end);
					double b = strtod(end, nullptr);
					gbSymbol.SetStrokeColor(geo3dml::Color(r, g, b));
				} else {
					SetStatus(false, color);
					break;
				}
			} else if (geo3dml::IsiEqual(localName, "Fill")) {
				std::string color;
				if (XMLReaderHelper::TextNode(reader, localName, color)) {
					char* end = nullptr;
					double r = strtod(color.c_str(), &end);
					double g = strtod(end, &end);
					double b = strtod(end, nullptr);
					gbSymbol.SetFillColor(geo3dml::Color(r, g, b));
				} else {
					SetStatus(false, color);
					break;
				}
			}
		}
		status = xmlTextReaderRead(reader);
	}
	if (!gbSymbol.IsEmpty()) {
		texture.SetGBSymbol(gbSymbol);
	}
	if (status != 1) {
		std::string err = XMLReaderHelper::FormatErrorMessageWithPosition(reader, "missing end element of " + texElemTag);
		SetStatus(false, err);
	}
	return IsOK();
}

const std::string XMLPBRMaterialReader::Element = "PBRMaterial";
