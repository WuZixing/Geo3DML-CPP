#include <g3dxml/XMLFeatureClassReader.h>
#include <g3dxml/XMLFeatureReader.h>
#include <g3dxml/XMLFieldReader.h>
#include <geo3dml/Utils.h>

using namespace g3dxml;

const std::string XMLFeatureClassReader::Element = "GeoFeatureClass";
const std::string XMLFeatureClassReader::Element_Name = "name";
const std::string XMLFeatureClassReader::Element_Schema = "Schema";

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
				featureClass->SetName(v);
			} else if (geo3dml::IsiEqual(localName, Element_Schema)) {
				if (!ReadSchema(reader, featureClass)) {
					break;
				}
			} else if (geo3dml::IsiEqual(localName, XMLFeatureReader::Element)) {
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
		if (nodeType == XML_READER_TYPE_END_ELEMENT && geo3dml::IsiEqual(localName, Element_Schema)) {
			break;
		} else if (nodeType == XML_READER_TYPE_ELEMENT) {
			if (geo3dml::IsiEqual(localName, XMLFieldReader::Element)) {
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
