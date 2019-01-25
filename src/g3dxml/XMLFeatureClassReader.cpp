#include <g3dxml/XMLFeatureClassReader.h>
#include <g3dxml/XMLFeatureReader.h>
#include <g3dxml/XMLFieldReader.h>

using namespace g3dxml;

std::string XMLFeatureClassReader::Element = "GeoFeatureClass";
std::string XMLFeatureClassReader::Element_Name = "name";
std::string XMLFeatureClassReader::Element_Schema = "Schema";

XMLFeatureClassReader::XMLFeatureClassReader(geo3dml::ObjectFactory* factory) {
	g3dFactory_ = factory;
}

XMLFeatureClassReader::~XMLFeatureClassReader() {
	g3dFactory_ = NULL;
}

geo3dml::FeatureClass* XMLFeatureClassReader::ReadFeatureClass(xmlTextReaderPtr reader) {
	geo3dml::FeatureClass* featureClass = g3dFactory_->NewFeatureClass();
	std::string fcId = XMLReaderHelper::AttributeGMLID(reader);
	if (fcId.empty()) {
		fcId = geo3dml::Object::NewID();
	}
	featureClass->SetID(fcId);
	bool metEndElement = false;
	int status = xmlTextReaderRead(reader);
	while (status == 1) {
		const char* localName = (const char*)xmlTextReaderConstLocalName(reader);
		int nodeType = xmlTextReaderNodeType(reader);
		if (nodeType == XML_READER_TYPE_END_ELEMENT && _stricmp(localName, Element.c_str()) == 0) {
			metEndElement = true;
			break;
		} else if (nodeType == XML_READER_TYPE_ELEMENT) {
			if (_stricmp(localName, Element_Name.c_str()) == 0) {
				std::string v;
				if (!XMLReaderHelper::TextNode(reader, Element_Name, v)) {
					SetStatus(false, v);
					break;
				}
				featureClass->SetName(v);
			} else if (_stricmp(localName, Element_Schema.c_str()) == 0) {
				if (!ReadSchema(reader, featureClass)) {
					break;
				}
			} else if (_stricmp(localName, XMLFeatureReader::Element.c_str()) == 0) {
				XMLFeatureReader featureReader(g3dFactory_);
				geo3dml::Feature* feature = featureReader.ReadFeature(reader);
				if (feature != NULL) {
					featureClass->AddFeature(feature);
				} else if (!featureReader.IsOK()) {
					SetStatus(false, featureReader.Error());
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
		delete featureClass;
		featureClass = NULL;
	}
	return featureClass;
}

bool XMLFeatureClassReader::ReadSchema(xmlTextReaderPtr reader, geo3dml::FeatureClass* f) {
	int status = xmlTextReaderRead(reader);
	while (status == 1) {
		const char* localName = (const char*)xmlTextReaderConstLocalName(reader);
		int nodeType = xmlTextReaderNodeType(reader);
		if (nodeType == XML_READER_TYPE_END_ELEMENT && _stricmp(localName, Element_Schema.c_str()) == 0) {
			break;
		} else if (nodeType == XML_READER_TYPE_ELEMENT) {
			if (_stricmp(localName, XMLFieldReader::Element.c_str()) == 0) {
				geo3dml::Field field;
				XMLFieldReader fieldReader;
				if (!fieldReader.ReadField(reader, &field)) {
					break;
				} else {
					f->AddField(field);
				}
			}
		}
		status = xmlTextReaderRead(reader);
	}
	if (status != 1) {
		std::string err = XMLReaderHelper::FormatErrorMessageWithPosition(reader, "missing end element of " + Element_Schema);
		SetStatus(false, err);
	}
	return IsOK();
}
