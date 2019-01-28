#include <g3dxml/XMLLineSymbolizerReader.h>
#include <g3dxml/XMLMaterialReader.h>

using namespace g3dxml;

std::string XMLLineSymbolizerReader::Element = "GeoLineSymbolizer";

XMLLineSymbolizerReader::XMLLineSymbolizerReader(geo3dml::ObjectFactory* factory) : Element_Stroke("Stroke") {
	g3dFactory_ = factory;
}

XMLLineSymbolizerReader::~XMLLineSymbolizerReader() {
	g3dFactory_ = NULL;
}

geo3dml::LineSymbolizer* XMLLineSymbolizerReader::ReadLineSym(xmlTextReaderPtr reader) {
	geo3dml::LineSymbolizer* lineSym = g3dFactory_->NewLineSymbolizer();
	int status = xmlTextReaderRead(reader);
	while (status == 1) {
		const char* localName = (const char*)xmlTextReaderConstLocalName(reader);
		int nodeType = xmlTextReaderNodeType(reader);
		if (nodeType == XML_READER_TYPE_END_ELEMENT && _stricmp(localName, Element.c_str()) == 0) {
			break;
		} else if (nodeType == XML_READER_TYPE_ELEMENT) {
			if (_stricmp(localName, Element_Stroke.c_str()) == 0) {
				if (!ReadStroke(reader, lineSym)) {
					break;
				}
			} else if (_stricmp(localName, XMLMaterialReader::Element.c_str()) == 0) {
				XMLMaterialReader materialReader(g3dFactory_);
				geo3dml::Material material;
				if (!materialReader.ReadMaterial(reader, material)) {
					SetStatus(false, materialReader.Error());
					break;
				}
				lineSym->SetMaterial(material);
			}
		}
		status = xmlTextReaderRead(reader);
	}
	if (status != 1) {
		std::string err = XMLReaderHelper::FormatErrorMessageWithPosition(reader, "missing end element of " + Element);
		SetStatus(false, err);
	}
	if (!IsOK()) {
		delete lineSym;
		lineSym = NULL;
	}
	return lineSym;
}

bool XMLLineSymbolizerReader::ReadStroke(xmlTextReaderPtr reader, geo3dml::LineSymbolizer* toLineSym) {
	int status = xmlTextReaderRead(reader);
	while (status == 1) {
		const char* localName = (const char*)xmlTextReaderConstLocalName(reader);
		int nodeType = xmlTextReaderNodeType(reader);
		if (nodeType == XML_READER_TYPE_END_ELEMENT && _stricmp(localName, Element_Stroke.c_str()) == 0) {
			break;
		} else if (nodeType == XML_READER_TYPE_ELEMENT) {
			if (_stricmp(localName, "SvgParameter") == 0) {
				std::string svgAttribute = XMLReaderHelper::Attribute(reader, "name");
				if (_stricmp(svgAttribute.c_str(), "stroke-width") == 0) {
					std::string strokeWidth;
					if (!XMLReaderHelper::TextNode(reader, "SvgParameter", strokeWidth)) {
						SetStatus(false, strokeWidth);
						break;
					}
					toLineSym->SetWidth(strtof(strokeWidth.c_str(), NULL));
				}
			}
		}
		status = xmlTextReaderRead(reader);
	}
	if (status != 1) {
		std::string err = XMLReaderHelper::FormatErrorMessageWithPosition(reader, "missing end element of " + Element_Stroke);
		SetStatus(false, err);
	}
	return IsOK();
}
