#include <g3dxml/XMLStyleReader.h>
#include <g3dxml/XMLFeatureTypeStyleReader.h>
#include <geo3dml/Utils.h>

using namespace g3dxml;

std::string XMLStyleReader::Element = "Geo3DStyle";
std::string XMLStyleReader::Element_Name = "name";

XMLStyleReader::XMLStyleReader(geo3dml::ObjectFactory* factory) {
	g3dFactory_ = factory;
}

XMLStyleReader::~XMLStyleReader() {
	g3dFactory_ = NULL;
}

geo3dml::Style* XMLStyleReader::ReadStyle(xmlTextReaderPtr reader) {
	geo3dml::Style* style = NULL;
	std::string styleId = XMLReaderHelper::AttributeGMLID(reader);
	if (styleId.empty()) {
		styleId = geo3dml::Object::NewID();
	}
	std::string styleName;
	int status = xmlTextReaderRead(reader);
	while (status == 1) {
		const char* localName = (const char*)xmlTextReaderConstLocalName(reader);
		int nodeType = xmlTextReaderNodeType(reader);
		if (nodeType == XML_READER_TYPE_END_ELEMENT && geo3dml::IsiEqual(localName, Element)) {
			break;
		} else if (nodeType == XML_READER_TYPE_ELEMENT) {
			if (geo3dml::IsiEqual(localName, Element_Name)) {
				if (!XMLReaderHelper::TextNode(reader, Element_Name, styleName)) {
					SetStatus(false, styleName);
					break;
				}
			} else if (geo3dml::IsiEqual(localName, XMLFeatureTypeStyleReader::Element)) {
				XMLFeatureTypeStyleReader ftStyleReader(g3dFactory_);
				style = ftStyleReader.ReadFeatureTypeStyle(reader);
				if (style == nullptr) {
					SetStatus(false, ftStyleReader.Error());
					break;
				}
			}
			/// TODO: read coverage style.
		}
		status = xmlTextReaderRead(reader);
	}
	if (style != nullptr) {
		style->SetID(styleId);
		style->SetName(styleName);
	}
	if (status != 1) {
		std::string err = XMLReaderHelper::FormatErrorMessageWithPosition(reader, "missing end element of " + Element);
		SetStatus(false, err);
	}
	if (!IsOK() && style != nullptr) {
		delete style;
		style = nullptr;
	}
	return style;
}
