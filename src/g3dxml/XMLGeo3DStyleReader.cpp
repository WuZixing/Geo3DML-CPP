#include <g3dxml/XMLGeo3DStyleReader.h>
#include <g3dxml/XMLFeatureTypeStyleReader.h>
#include <geo3dml/Utils.h>

using namespace g3dxml;

std::string XMLGeo3DStyleReader::Element = "Geo3DStyle";
std::string XMLGeo3DStyleReader::Element_Name = "name";

XMLGeo3DStyleReader::XMLGeo3DStyleReader(geo3dml::ObjectFactory* factory) {
	g3dFactory_ = factory;
}

XMLGeo3DStyleReader::~XMLGeo3DStyleReader() {
	g3dFactory_ = NULL;
}

geo3dml::Geo3DStyle* XMLGeo3DStyleReader::ReadStyle(xmlTextReaderPtr reader) {
	geo3dml::Geo3DStyle* style = NULL;
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
				if (style != NULL) {
					style->SetName(styleName);
				}
			} else if (geo3dml::IsiEqual(localName, XMLFeatureTypeStyleReader::Element)) {
				XMLFeatureTypeStyleReader ftStyleReader(g3dFactory_);
				style = ftStyleReader.ReadFeatureTypeStyle(reader);
				if (style != NULL) {
					style->SetName(styleName);
				} else {
					SetStatus(false, ftStyleReader.Error());
					break;
				}
			}
			/// TODO: read coverage style.
		}
		status = xmlTextReaderRead(reader);
	}
	if (status != 1) {
		std::string err = XMLReaderHelper::FormatErrorMessageWithPosition(reader, "missing end element of " + Element);
		SetStatus(false, err);
	}
	if (!IsOK() && style != NULL) {
		delete style;
		style = NULL;
	}
	return style;
}
