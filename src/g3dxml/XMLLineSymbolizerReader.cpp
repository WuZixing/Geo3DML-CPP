#include <g3dxml/XMLLineSymbolizerReader.h>
#include <g3dxml/XMLMaterialReader.h>
#include <geo3dml/Utils.h>

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
		if (nodeType == XML_READER_TYPE_END_ELEMENT && geo3dml::IsiEqual(localName, Element)) {
			break;
		} else if (nodeType == XML_READER_TYPE_ELEMENT) {
			if (geo3dml::IsiEqual(localName, Element_Stroke)) {
				if (!ReadStroke(reader, lineSym)) {
					break;
				}
			} else if (geo3dml::IsiEqual(localName, XMLMaterialReader::Element)) {
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
		if (nodeType == XML_READER_TYPE_END_ELEMENT && geo3dml::IsiEqual(localName, Element_Stroke)) {
			break;
		} else if (nodeType == XML_READER_TYPE_ELEMENT) {
			if (geo3dml::IsiEqual(localName, "SvgParameter")) {
				std::string svgAttribute = XMLReaderHelper::Attribute(reader, "name");
				if (geo3dml::IsiEqual(svgAttribute, "stroke-width")) {
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
