#include <g3dxml/XMLGeoDiscreteCoverageReader.h>
#include <g3dxml/XMLFieldReader.h>

using namespace g3dxml;

std::string XMLGeoDiscreteCoverageReader::Element = "GeoDiscreteCoverage";
std::string XMLGeoDiscreteCoverageReader::Element_RangeType = "rangeType";
std::string XMLGeoDiscreteCoverageReader::Element_RangeSet = "rangeSet";

XMLGeoDiscreteCoverageReader::XMLGeoDiscreteCoverageReader(geo3dml::ObjectFactory* factory) {
	g3dFactory_ = factory;
}

XMLGeoDiscreteCoverageReader::~XMLGeoDiscreteCoverageReader() {

}

bool XMLGeoDiscreteCoverageReader::ReadGeoDiscreteCoverage(xmlTextReaderPtr reader, geo3dml::Shape* toShape) {
	geo3dml::ShapeProperty* shapeProperty = g3dFactory_->NewShapeProperty();
	std::string coverageName;
	std::string coverageId = XMLReaderHelper::AttributeGMLID(reader);
	shapeProperty->SetID(coverageId);
	int status = xmlTextReaderRead(reader);
	while (status == 1) {
		const char* localName = (const char*)xmlTextReaderConstLocalName(reader);
		int nodeType = xmlTextReaderNodeType(reader);
		if (nodeType == XML_READER_TYPE_END_ELEMENT && _stricmp(localName, Element.c_str()) == 0) {
			break;
		} else if (nodeType == XML_READER_TYPE_ELEMENT) {
			if (_stricmp(localName, "SamplingTarget") == 0) {
				std::string targetName;
				if (!XMLReaderHelper::TextNode(reader, "SamplingTarget", targetName)) {
					SetStatus(false, targetName);
					break;
				}
				toShape->SetProperty(shapeProperty, geo3dml::ShapeProperty::NameToSamplingTarget(targetName));
			} else if (_stricmp(localName, "name") == 0) {
				if (!XMLReaderHelper::TextNode(reader, "name", coverageName)) {
					SetStatus(false, coverageName);
					break;
				}
				shapeProperty->Name(coverageName);
			} else if (_stricmp(localName, "Version") == 0) {
				std::string timestamp = XMLReaderHelper::Attribute(reader, "Timestamp");
				std::string versionNo;
				if (!XMLReaderHelper::TextNode(reader, "Version", versionNo)) {
					SetStatus(false, versionNo);
					break;
				}
				geo3dml::ShapeProperty::Version vInfo;
				vInfo.VersionNo(versionNo).Timestamp(timestamp);
				shapeProperty->VersionInfo(vInfo);
			} else if (_stricmp(localName, Element_RangeType.c_str()) == 0) {
				if (!ReadRangeType(reader, shapeProperty)) {
					break;
				}
			} else if (_stricmp(localName, Element_RangeSet.c_str()) == 0) {
				if (!ReadRangeSet(reader, shapeProperty)) {
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
	return IsOK();
}

bool XMLGeoDiscreteCoverageReader::ReadRangeType(xmlTextReaderPtr reader, geo3dml::ShapeProperty* shapeProperty) {
	int status = xmlTextReaderRead(reader);
	while (status == 1) {
		const char* localName = (const char*)xmlTextReaderConstLocalName(reader);
		int nodeType = xmlTextReaderNodeType(reader);
		if (nodeType == XML_READER_TYPE_END_ELEMENT && _stricmp(localName, Element_RangeType.c_str()) == 0) {
			break;
		} else if (nodeType == XML_READER_TYPE_ELEMENT) {
			if (_stricmp(localName, XMLFieldReader::Element.c_str()) == 0) {
				geo3dml::Field field;
				XMLFieldReader fieldReader;
				if (!fieldReader.ReadField(reader, &field)) {
					break;
				} else {
					shapeProperty->AddField(field);
				}
			}
		}
		status = xmlTextReaderRead(reader);
	}
	if (status != 1) {
		std::string err = XMLReaderHelper::FormatErrorMessageWithPosition(reader, "missing end element of " + Element_RangeType);
		SetStatus(false, err);
	}
	return IsOK();
}

bool XMLGeoDiscreteCoverageReader::ReadRangeSet(xmlTextReaderPtr reader, geo3dml::ShapeProperty* shapeProperty) {
	int fieldIndex = 0;
	int status = xmlTextReaderRead(reader);
	while (status == 1) {
		const char* localName = (const char*)xmlTextReaderConstLocalName(reader);
		int nodeType = xmlTextReaderNodeType(reader);
		if (nodeType == XML_READER_TYPE_END_ELEMENT && _stricmp(localName, Element_RangeSet.c_str()) == 0) {
			break;
		} else if (nodeType == XML_READER_TYPE_ELEMENT) {
			if (_stricmp(localName, "ValueArray") == 0) {
				if (!ReadRangeSetField(reader, shapeProperty, fieldIndex)) {
					break;
				}
				++fieldIndex;
			}
		}
		status = xmlTextReaderRead(reader);
	}
	if (status != 1) {
		std::string err = XMLReaderHelper::FormatErrorMessageWithPosition(reader, "missing end element of " + Element_RangeSet);
		SetStatus(false, err);
	}
	return IsOK();
}

bool XMLGeoDiscreteCoverageReader::ReadRangeSetField(xmlTextReaderPtr reader, geo3dml::ShapeProperty* shapeProperty, int fieldIndex) {
	const std::string elementName = "ValueArray";
	int status = xmlTextReaderRead(reader);
	while (status == 1) {
		const char* localName = (const char*)xmlTextReaderConstLocalName(reader);
		int nodeType = xmlTextReaderNodeType(reader);
		if (nodeType == XML_READER_TYPE_END_ELEMENT && _stricmp(localName, elementName.c_str()) == 0) {
			break;
		} else if (nodeType == XML_READER_TYPE_ELEMENT) {
			if (_stricmp(localName, "valueComponents") == 0) {
				if (!ReadFieldValues(reader, shapeProperty, fieldIndex)) {
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

bool XMLGeoDiscreteCoverageReader::ReadFieldValues(xmlTextReaderPtr reader, geo3dml::ShapeProperty* shapeProperty, int fieldIndex) {
	const std::string elementName = "valueComponents";
	unsigned int valueIndex = 0;
	int status = xmlTextReaderRead(reader);
	while (status == 1) {
		const char* localName = (const char*)xmlTextReaderConstLocalName(reader);
		int nodeType = xmlTextReaderNodeType(reader);
		if (nodeType == XML_READER_TYPE_END_ELEMENT && _stricmp(localName, elementName.c_str()) == 0) {
			break;
		} else if (nodeType == XML_READER_TYPE_ELEMENT) {
			if (_stricmp(localName, "Quantity") == 0) {
				// double value
				std::string str;
				if (XMLReaderHelper::TextNode(reader, "Quantity", str)) {
					double v = atof(str.c_str());
					shapeProperty->DoubleValue(fieldIndex, valueIndex++, v);
				} else {
					SetStatus(false, str);
					break;
				}
			} else if (_stricmp(localName, "Count") == 0) {
				// int value
				std::string str;
				if (XMLReaderHelper::TextNode(reader, "Count", str)) {
					int v = atoi(str.c_str());
					shapeProperty->IntValue(fieldIndex, valueIndex++, v);
				} else {
					SetStatus(false, str);
					break;
				}
			} else if (_stricmp(localName, "Text") == 0) {
				// string value
				std::string str;
				if (XMLReaderHelper::TextNode(reader, "Text", str)) {
					shapeProperty->TextValue(fieldIndex, valueIndex++, str);
				} else {
					SetStatus(false, str);
					break;
				}
			} else if (_stricmp(localName, "ValueArray") == 0) {
				// array value
				if (!ReadElementValueAsArray(reader, shapeProperty, fieldIndex)) {
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

bool XMLGeoDiscreteCoverageReader::ReadElementValueAsArray(xmlTextReaderPtr reader, geo3dml::ShapeProperty* shapeProperty, int fieldIndex) {
	const std::string elementName = "ValueArray";
	unsigned int iteratorLevel = 0;
	int status = xmlTextReaderRead(reader);
	while (status == 1) {
		const char* localName = (const char*)xmlTextReaderConstLocalName(reader);
		int nodeType = xmlTextReaderNodeType(reader);
		if (nodeType == XML_READER_TYPE_END_ELEMENT && _stricmp(localName, elementName.c_str()) == 0) {
			if (iteratorLevel > 0) {
				--iteratorLevel;
			} else {
				break;
			}
		} else if (nodeType == XML_READER_TYPE_ELEMENT) {
			if (_stricmp(localName, elementName.c_str()) == 0) {
				++iteratorLevel;
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
