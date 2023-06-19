#include <g3dxml/XMLFeatureReader.h>
#include <g3dxml/XMLGeometryReader.h>
#include <g3dxml/XMLFieldReader.h>
#include <geo3dml/FieldValue.h>
#include <geo3dml/Utils.h>

using namespace g3dxml;

std::string XMLFeatureReader::Element = "GeoFeature";
std::string XMLFeatureReader::Element_Name = "name";
std::string XMLFeatureReader::Element_Fields = "Fields";

XMLFeatureReader::XMLFeatureReader(geo3dml::ObjectFactory* factory) {
	g3dFactory_ = factory;
}

XMLFeatureReader::~XMLFeatureReader() {
	g3dFactory_ = NULL;
}

geo3dml::Feature* XMLFeatureReader::ReadFeature(xmlTextReaderPtr reader) {
	geo3dml::Feature* feature = g3dFactory_->NewFeature();
	std::string featureId = XMLReaderHelper::AttributeGMLID(reader);
	if (featureId.empty()) {
		featureId = geo3dml::Object::NewID();
	}
	feature->SetID(featureId);
	int status = xmlTextReaderRead(reader);
	while (status == 1) {
		const char* localName = (const char*)xmlTextReaderConstLocalName(reader);
		int nodeType = xmlTextReaderNodeType(reader);
		if (nodeType == XML_READER_TYPE_END_ELEMENT && geo3dml::IsiEqual(localName, Element)) {
			break;
		} else if (nodeType == XML_READER_TYPE_ELEMENT) {
			if (geo3dml::IsiEqual(localName, Element_Name)) {
				std::string name;
				if (!XMLReaderHelper::TextNode(reader, Element_Name, name)) {
					SetStatus(false, name);
					break;
				}
				feature->SetName(name);
			} else if (geo3dml::IsiEqual(localName, Element_Fields)) {
				if (!ReadFields(reader, feature)) {
					break;
				}
			} else if (geo3dml::IsiEqual(localName, XMLGeometryReader::Element)) {
				XMLGeometryReader geoReader(g3dFactory_);
				geo3dml::Geometry* geometry = geoReader.ReadGeometry(reader);
				if (geometry != NULL) {
					feature->SetGeometry(geometry);
				} else if (!geoReader.IsOK()) {
					SetStatus(false, geoReader.Error());
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
		delete feature;
		feature = NULL;
	}
	return feature;
}

bool XMLFeatureReader::ReadFields(xmlTextReaderPtr reader, geo3dml::Feature* feature) {
	int status = xmlTextReaderRead(reader);
	while (status == 1) {
		const char* localName = (const char*)xmlTextReaderConstLocalName(reader);
		int nodeType = xmlTextReaderNodeType(reader);
		if (nodeType == XML_READER_TYPE_END_ELEMENT && geo3dml::IsiEqual(localName, Element_Fields)) {
			break;
		} else if (nodeType == XML_READER_TYPE_ELEMENT) {
			if (geo3dml::IsiEqual(localName, "Field")) {
				if (!ReadField(reader, feature)) {
					break;
				}
			}
		}
		status = xmlTextReaderRead(reader);
	}
	if (status != 1) {
		std::string err = XMLReaderHelper::FormatErrorMessageWithPosition(reader, "missing end element of " + Element_Fields);
		SetStatus(false, err);
	}
	return IsOK();
}

bool XMLFeatureReader::ReadField(xmlTextReaderPtr reader, geo3dml::Feature* feature) {
	std::string fieldName = XMLReaderHelper::Attribute(reader, "Name");
	int status = xmlTextReaderRead(reader);
	while (status == 1) {
		const char* localName = (const char*)xmlTextReaderConstLocalName(reader);
		int nodeType = xmlTextReaderNodeType(reader);
		if (nodeType == XML_READER_TYPE_END_ELEMENT && geo3dml::IsiEqual(localName, "Field")) {
			break;
		} else if (nodeType == XML_READER_TYPE_ELEMENT) {
			geo3dml::FieldValue fieldValue(fieldName);
			geo3dml::Field::ValueType vType = XMLFieldReader::NameToValueType(localName);
			if (ReadFieldValue(reader, localName, vType, &fieldValue)) {
				feature->SetField(fieldValue);
			}
			if (!IsOK()) {
				break;
			}
		}
		status = xmlTextReaderRead(reader);
	}
	if (status != 1) {
		std::string err = XMLReaderHelper::FormatErrorMessageWithPosition(reader, "missing end element of Field");
		SetStatus(false, err);
	}
	return IsOK();
}

bool XMLFeatureReader::ReadFieldValue(xmlTextReaderPtr reader, const std::string& elementName, geo3dml::Field::ValueType valueType, geo3dml::FieldValue* value) {
	int status = xmlTextReaderRead(reader);
	while (status == 1) {
		const char* localName = (const char*)xmlTextReaderConstLocalName(reader);
		int nodeType = xmlTextReaderNodeType(reader);
		if (nodeType == XML_READER_TYPE_END_ELEMENT && geo3dml::IsiEqual(localName, elementName)) {
			break;
		} else if (nodeType == XML_READER_TYPE_ELEMENT) {
			if (geo3dml::IsiEqual(localName, "value")) {
				std::string v;
				if (!XMLReaderHelper::TextNode(reader, "value", v)) {
					SetStatus(false, v);
					break;
				}
				switch (valueType) {
				case geo3dml::Field::ValueType::Boolean: {
					value->SetBool(geo3dml::IsTrue(v));
					break;
				}
				case geo3dml::Field::ValueType::Integer: {
					value->SetInt(atoi(v.c_str()));
					break;
				}
				case geo3dml::Field::ValueType::Double: {
					value->SetDouble(atof(v.c_str()));
					break;
				}
				case geo3dml::Field::ValueType::Text: {
					value->SetString(v);
					break;
				}
				default: {
					std::string err = XMLReaderHelper::FormatErrorMessageWithPosition(reader, "unknown value type: " + XMLFieldReader::ValueTypeToName(value->ValueType()) + " with field name of " + value->FieldName());
					SetStatus(false, err);
					break;
				}
				}
				if (!IsOK()) {
					break;
				}
			}
		}
		status = xmlTextReaderRead(reader);
	}
	if (status != 1) {
		std::string err = XMLReaderHelper::FormatErrorMessageWithPosition(reader, "missing end element of " + elementName);
		SetStatus(false, err);
	}
	return IsOK();
}
