#include <g3dxml/XMLLayerReader.h>
#include <g3dxml/XMLStyleReader.h>
#include <geo3dml/Utils.h>

using namespace g3dxml;

std::string XMLLayerReader::Element = "Layer";
std::string XMLLayerReader::Element_Name = "name";
std::string XMLLayerReader::Element_FeatureClass= "FeatureClass";

XMLLayerReader::XMLLayerReader(geo3dml::ObjectFactory* factory) {
	g3dFactory_ = factory;
}

XMLLayerReader::~XMLLayerReader() {
	g3dFactory_ = NULL;
}

geo3dml::Layer* XMLLayerReader::ReadLayer(xmlTextReaderPtr reader) {
	geo3dml::Layer* layer = g3dFactory_->NewLayer();
	std::string layerId = XMLReaderHelper::AttributeGMLID(reader);
	if (layerId.empty()) {
		layerId = geo3dml::Object::NewID();
	}
	layer->SetID(layerId);
	int status = xmlTextReaderRead(reader);
	while (status == 1) {
		const char* localName = (const char*)xmlTextReaderConstLocalName(reader);
		int nodeType = xmlTextReaderNodeType(reader);
		if (nodeType == XML_READER_TYPE_END_ELEMENT && geo3dml::IsiEqual(localName, Element)) {
			break;
		} else if (nodeType == XML_READER_TYPE_ELEMENT) {
			if (geo3dml::IsiEqual(localName, Element_Name)) {
				std::string v;
				if (!XMLReaderHelper::TextNode(reader, Element_Name, v)) {
					SetStatus(false, v);
					break;
				}
				layer->SetName(v);
			} else if (geo3dml::IsiEqual(localName, Element_FeatureClass)) {
				xmlChar* href = xmlTextReaderGetAttribute(reader, (const xmlChar*)"href");
				if (href == NULL) {
					href = xmlTextReaderGetAttribute(reader, (const xmlChar*)"xlink:href");
				}
				if (href != NULL) {
					std::string fcID((const char*)href);
					fcID = fcID.substr(fcID.find_last_of('#') + 1);
					layer->SetBindingFeatureClassID(fcID);
					xmlFree(href);
				} else {
					std::string err = XMLReaderHelper::FormatErrorMessageWithPosition(reader, "missing attribute of xlink:href");
					SetStatus(false, err);
					break;
				}
			} else if (geo3dml::IsiEqual(localName, XMLStyleReader::Element)) {
				XMLStyleReader styleReader(g3dFactory_);
				geo3dml::Style* style = styleReader.ReadStyle(reader);
				if (style != NULL) {
					layer->AddStyle(style);
				} else if (!styleReader.IsOK()) {
					SetStatus(false, styleReader.Error());
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
	if (!IsOK()) {
		delete layer;
		layer = NULL;
	}
	return layer;
}
