#include <g3dxml/XMLFieldReader.h>

using namespace g3dxml;

std::string XMLFieldReader::Element = "field";

geo3dml::Field::ValueType XMLFieldReader::NameToValueType(const std::string& n) {
	if (_stricmp(n.c_str(), "Text") == 0) {
		return geo3dml::Field::Text;
	} else if (_stricmp(n.c_str(), "Quantity") == 0) {
		return geo3dml::Field::Double;
	} else if (_stricmp(n.c_str(), "Count") == 0) {
		return geo3dml::Field::Integer;
	} else if (_stricmp(n.c_str(), "Boolean") == 0) {
		return geo3dml::Field::Boolean;
	} else {
		return geo3dml::Field::Unknown;
	}
}

std::string XMLFieldReader::ValueTypeToName(geo3dml::Field::ValueType t) {
	switch (t) {
	case geo3dml::Field::Text:
		return "Text";
	case geo3dml::Field::Integer:
		return "Count";
	case geo3dml::Field::Double:
		return "Quantity";
	case geo3dml::Field::Boolean:
		return "Boolean";
	default:
		return "Unknown";
	}
}

bool XMLFieldReader::ReadField(xmlTextReaderPtr reader, geo3dml::Field* field) {
	std::string fieldName = XMLReaderHelper::Attribute(reader, "name");
	field->Name(fieldName).Label(fieldName);
	int status = xmlTextReaderRead(reader);
	while (status == 1) {
		const char* localName = (const char*)xmlTextReaderConstLocalName(reader);
		int nodeType = xmlTextReaderNodeType(reader);
		if (nodeType == XML_READER_TYPE_END_ELEMENT && _stricmp(localName, Element.c_str()) == 0) {
			break;
		} else if (nodeType == XML_READER_TYPE_ELEMENT) {
			geo3dml::Field::ValueType vType = NameToValueType(localName);
			if (vType != geo3dml::Field::Unknown) {
				field->DataType(vType);
				if (!ReadFieldDefinition(reader, localName, field)) {
					break;
				}
			} else {
				std::string err = XMLReaderHelper::FormatErrorMessageWithPosition(reader, std::string("unknown field: ") + std::string(localName));
				SetStatus(false, err);
				break;
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

bool XMLFieldReader::ReadFieldDefinition(xmlTextReaderPtr reader, const std::string& fieldElementName, geo3dml::Field* field) {
	if (xmlTextReaderIsEmptyElement(reader)) {
		return true;
	}
	field->Definition(XMLReaderHelper::Attribute(reader, "definition"));
	int status = xmlTextReaderRead(reader);
	while (status == 1) {
		const char* localName = (const char*)xmlTextReaderConstLocalName(reader);
		int nodeType = xmlTextReaderNodeType(reader);
		if (nodeType == XML_READER_TYPE_END_ELEMENT && _stricmp(localName, fieldElementName.c_str()) == 0) {
			break;
		} else if (nodeType == XML_READER_TYPE_ELEMENT) {
			if (_stricmp(localName, "label") == 0) {
				std::string label;
				if (XMLReaderHelper::TextNode(reader, "label", label)) {
					field->Label(label);
				} else {
					SetStatus(false, label);
					break;
				}
			} else if (_stricmp(localName, "description") == 0) {
				std::string description;
				if (XMLReaderHelper::TextNode(reader, "description", description)) {
					field->Description(description);
				} else {
					SetStatus(false, description);
					break;
				}
			} else if (_stricmp(localName, "uom") == 0) {
				std::string uom = XMLReaderHelper::Attribute(reader, "code");
				field->Uom(uom);
			}
		}
		status = xmlTextReaderRead(reader);
	}
	if (status != 1) {
		std::string err = XMLReaderHelper::FormatErrorMessageWithPosition(reader, "missing end element of " + fieldElementName);
		SetStatus(false, err);
	}
	return IsOK();
}

void XMLFieldReader::WriteField(const geo3dml::Field& field, std::ostream& output) {
	output << "<swe:field name=\"" << field.Name() << "\">" << std::endl;
	output << "<swe:" << XMLFieldReader::ValueTypeToName(field.DataType());
	std::string definition = field.Definition();
	if (definition.length() > 0) {
		output << " definition=\"" << definition << "\"";
	}
	output << ">" << std::endl;
	std::string label = field.Label();
	if (label.length() > 0) {
		output << "<swe:label>" << label << "</swe:label>" << std::endl;
	}
	std::string description = field.Description();
	if (description.length() > 0) {
		output << "<swe:description>" << description << "</swe:description>" << std::endl;
	}
	std::string uom = field.Uom();
	if (uom.length() > 0) {
		output << "<swe:uom>" << uom << "</swe:uom>" << std::endl;
	}
	output << "</swe:" << XMLFieldReader::ValueTypeToName(field.DataType()) << ">" << std::endl;
	output << "</swe:field>" << std::endl;
}
