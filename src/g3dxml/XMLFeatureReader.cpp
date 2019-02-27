#include <g3dxml/XMLFeatureReader.h>
#include <g3dxml/XMLGeometryReader.h>
#include <g3dxml/XMLFieldReader.h>
#include <geo3dml/FieldValue.h>

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
		if (nodeType == XML_READER_TYPE_END_ELEMENT && _stricmp(localName, Element.c_str()) == 0) {
			break;
		} else if (nodeType == XML_READER_TYPE_ELEMENT) {
			if (_stricmp(localName, Element_Name.c_str()) == 0) {
				std::string name;
				if (!XMLReaderHelper::TextNode(reader, Element_Name, name)) {
					SetStatus(false, name);
					break;
				}
				feature->SetName(name);
			} else if (_stricmp(localName, Element_Fields.c_str()) == 0) {
				if (!ReadFields(reader, feature)) {
					break;
				}
			} else if (_stricmp(localName, XMLGeometryReader::Element.c_str()) == 0) {
				XMLGeometryReader geoReader(g3dFactory_);
				geo3dml::Geometry* geometry = geoReader.ReadGeometry(reader);
				if (geometry != NULL) {
					feature->AddGeometry(geometry);
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
		if (nodeType == XML_READER_TYPE_END_ELEMENT && _stricmp(localName, Element_Fields.c_str()) == 0) {
			break;
		} else if (nodeType == XML_READER_TYPE_ELEMENT) {
			if (_stricmp(localName, "Field") == 0) {
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
		if (nodeType == XML_READER_TYPE_END_ELEMENT && _stricmp(localName, "Field") == 0) {
			break;
		} else if (nodeType == XML_READER_TYPE_ELEMENT) {
			geo3dml::Field::ValueType vType = XMLFieldReader::NameToValueType(localName);
			switch (vType) {
			case geo3dml::Field::Text: {
				geo3dml::TextFieldValue* textValue = new geo3dml::TextFieldValue(fieldName);
				if (ReadFieldValue(reader, localName, textValue)) {
					feature->SetField(textValue);
				} else {
					delete textValue;
				}
				break;
			}
			case geo3dml::Field::Integer: {
				geo3dml::IntegerFieldValue* intValue = new geo3dml::IntegerFieldValue(fieldName);
				if (ReadFieldValue(reader, localName, intValue)) {
					feature->SetField(intValue);
				} else {
					delete intValue;
				}
				break;
			}
			case geo3dml::Field::Double: {
				geo3dml::DoubleFieldValue* doubleValue = new geo3dml::DoubleFieldValue(fieldName);
				if (ReadFieldValue(reader, localName, doubleValue)) {
					feature->SetField(doubleValue);
				} else {
					delete doubleValue;
				}
				break;
			}
			case geo3dml::Field::Boolean: {
				geo3dml::BooleanFieldValue* boolValue = new geo3dml::BooleanFieldValue(fieldName);
				if (ReadFieldValue(reader, localName, boolValue)) {
					feature->SetField(boolValue);
				} else {
					delete boolValue;
				}
				break;
			}
			default: {
				std::string err = XMLReaderHelper::FormatErrorMessageWithPosition(reader, std::string("unknown field: ") + std::string(localName));
				SetStatus(false, err);
				break;
			}
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

bool XMLFeatureReader::ReadFieldValue(xmlTextReaderPtr reader, const std::string& elementName, geo3dml::FieldValue* value) {
	int status = xmlTextReaderRead(reader);
	while (status == 1) {
		const char* localName = (const char*)xmlTextReaderConstLocalName(reader);
		int nodeType = xmlTextReaderNodeType(reader);
		if (nodeType == XML_READER_TYPE_END_ELEMENT && _stricmp(localName, elementName.c_str()) == 0) {
			break;
		} else if (nodeType == XML_READER_TYPE_ELEMENT) {
			if (_stricmp(localName, "value") == 0) {
				std::string v;
				if (!XMLReaderHelper::TextNode(reader, "value", v)) {
					SetStatus(false, v);
					break;
				}
				geo3dml::TextFieldValue* textValue = dynamic_cast<geo3dml::TextFieldValue*>(value);
				if (textValue != NULL) {
					textValue->Value(v);
				} else {
					geo3dml::DoubleFieldValue* doubleValue = dynamic_cast<geo3dml::DoubleFieldValue*>(value);
					if (doubleValue != NULL) {
						doubleValue->Value(atof(v.c_str()));
					} else {
						geo3dml::IntegerFieldValue* intValue = dynamic_cast<geo3dml::IntegerFieldValue*>(value);
						if (intValue != NULL) {
							intValue->Value(atoi(v.c_str()));
						} else {
							geo3dml::BooleanFieldValue* boolValue = dynamic_cast<geo3dml::BooleanFieldValue*>(value);
							if (boolValue != NULL) {
								boolValue->Value(XMLReaderHelper::IsTrue(v));
							} else {
								std::string err = XMLReaderHelper::FormatErrorMessageWithPosition(reader, "unknown value type: " + XMLFieldReader::ValueTypeToName(value->ValueType()) + " with field name of " + value->FieldName());
								SetStatus(false, err);
								break;
							}
						}
					}
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
