// UTF-8编码
#include <g3dxml/XMLGeoDiscreteCoverageReader.h>
#include <g3dxml/XMLFieldReader.h>
#include <geo3dml/Utils.h>

using namespace g3dxml;

const std::string XMLGeoDiscreteCoverageReader::Element = "GeoDiscreteCoverage";
const std::string XMLGeoDiscreteCoverageReader::Element_RangeType = "rangeType";
const std::string XMLGeoDiscreteCoverageReader::Element_RangeSet = "rangeSet";

XMLGeoDiscreteCoverageReader::XMLGeoDiscreteCoverageReader(geo3dml::ObjectFactory* factory) {
	g3dFactory_ = factory;
}

XMLGeoDiscreteCoverageReader::~XMLGeoDiscreteCoverageReader() {

}

bool XMLGeoDiscreteCoverageReader::ReadGeoDiscreteCoverage(xmlTextReaderPtr reader, geo3dml::Geometry* toShape) {
	geo3dml::ShapeProperty* shapeProperty = g3dFactory_->NewShapeProperty();
	std::string coverageName;
	std::string coverageId = XMLReaderHelper::AttributeGMLID(reader);
	shapeProperty->SetID(coverageId);
	int status = xmlTextReaderRead(reader);
	while (status == 1) {
		const char* localName = (const char*)xmlTextReaderConstLocalName(reader);
		int nodeType = xmlTextReaderNodeType(reader);
		if (nodeType == XML_READER_TYPE_END_ELEMENT && geo3dml::IsiEqual(localName, Element)) {
			break;
		} else if (nodeType == XML_READER_TYPE_ELEMENT) {
			if (geo3dml::IsiEqual(localName, "SamplingTarget")) {
				std::string targetName;
				if (!XMLReaderHelper::TextNode(reader, "SamplingTarget", targetName)) {
					SetStatus(false, targetName);
					break;
				}
				toShape->SetProperty(shapeProperty, geo3dml::ShapeProperty::NameToSamplingTarget(targetName));
			} else if (geo3dml::IsiEqual(localName, "name")) {
				if (!XMLReaderHelper::TextNode(reader, "name", coverageName)) {
					SetStatus(false, coverageName);
					break;
				}
				shapeProperty->Name(coverageName);
			} else if (geo3dml::IsiEqual(localName, "Version")) {
				std::string timestamp = XMLReaderHelper::Attribute(reader, "Timestamp");
				std::string versionNo;
				if (!XMLReaderHelper::TextNode(reader, "Version", versionNo)) {
					SetStatus(false, versionNo);
					break;
				}
				geo3dml::ShapeProperty::Version vInfo;
				vInfo.VersionNo(versionNo).Timestamp(timestamp);
				shapeProperty->VersionInfo(vInfo);
			} else if (geo3dml::IsiEqual(localName, Element_RangeType)) {
				if (!ReadRangeType(reader, shapeProperty)) {
					break;
				}
			} else if (geo3dml::IsiEqual(localName, Element_RangeSet)) {
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
		if (nodeType == XML_READER_TYPE_END_ELEMENT && geo3dml::IsiEqual(localName, Element_RangeType)) {
			break;
		} else if (nodeType == XML_READER_TYPE_ELEMENT) {
			if (geo3dml::IsiEqual(localName, XMLFieldReader::Element)) {
				geo3dml::Field field;
				XMLFieldReader fieldReader;
				if (fieldReader.ReadField(reader, &field) && field.DataType() != geo3dml::Field::ValueType::Unknown) {
					// 当前仅支持文本，整数、浮点数和布尔类型的字段。
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
		if (nodeType == XML_READER_TYPE_END_ELEMENT && geo3dml::IsiEqual(localName, Element_RangeSet)) {
			break;
		} else if (nodeType == XML_READER_TYPE_ELEMENT) {
			if (geo3dml::IsiEqual(localName, "ValueArray")) {
				if (ReadRangeSetField(reader, shapeProperty, fieldIndex)) {
					++fieldIndex;
				} else {
					SetStatus(true);	// 重置错误（如不支持的属性类型值造成的错误），继续读取后续的值。
				}
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
		if (nodeType == XML_READER_TYPE_END_ELEMENT && geo3dml::IsiEqual(localName, elementName)) {
			break;
		} else if (nodeType == XML_READER_TYPE_ELEMENT) {
			if (geo3dml::IsiEqual(localName, "valueComponents")) {
				ReadFieldValues(reader, shapeProperty, fieldIndex);
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
		if (nodeType == XML_READER_TYPE_END_ELEMENT && geo3dml::IsiEqual(localName, elementName)) {
			break;
		} else if (nodeType == XML_READER_TYPE_ELEMENT) {
			if (geo3dml::IsiEqual(localName, "Quantity")) {
				// double value
				std::string str;
				if (XMLReaderHelper::TextNode(reader, "Quantity", str)) {
					double v = atof(str.c_str());
					shapeProperty->DoubleValue(fieldIndex, valueIndex, v);
				} else {
					SetStatus(false, str);
				}
			} else if (geo3dml::IsiEqual(localName, "Count")) {
				// int value
				std::string str;
				if (XMLReaderHelper::TextNode(reader, "Count", str)) {
					int v = atoi(str.c_str());
					shapeProperty->IntValue(fieldIndex, valueIndex, v);
				} else {
					SetStatus(false, str);
				}
			} else if (geo3dml::IsiEqual(localName, "Text")) {
				// string value
				std::string str;
				if (XMLReaderHelper::TextNode(reader, "Text", str)) {
					shapeProperty->TextValue(fieldIndex, valueIndex, str);
				} else {
					SetStatus(false, str);
				}
			} else if (geo3dml::IsiEqual(localName, "Category")) {
				// Category的取值为字符串
				std::string str;
				if (XMLReaderHelper::TextNode(reader, "Category", str)) {
					shapeProperty->TextValue(fieldIndex, valueIndex, str);
				} else {
					SetStatus(false, str);
				}
			} else {
				ReadElementValueAsOther(reader, localName);
				std::string err = XMLReaderHelper::FormatErrorMessageWithPosition(reader, "unknown value: " + elementName);
				SetStatus(false, err);
			}
			++valueIndex;
		}
		status = xmlTextReaderRead(reader);
	}
	if (status != 1) {
		std::string err = XMLReaderHelper::FormatErrorMessageWithPosition(reader, "missing end element of " + elementName);
		SetStatus(false, err);
	}
	return IsOK();
}

bool XMLGeoDiscreteCoverageReader::ReadElementValueAsOther(xmlTextReaderPtr reader, const std::string& elemName) {
	unsigned int iteratorLevel = 0;
	int status = xmlTextReaderRead(reader);
	while (status == 1) {
		const char* localName = (const char*)xmlTextReaderConstLocalName(reader);
		int nodeType = xmlTextReaderNodeType(reader);
		if (nodeType == XML_READER_TYPE_END_ELEMENT && geo3dml::IsiEqual(localName, elemName)) {
			if (iteratorLevel > 0) {
				--iteratorLevel;
			} else {
				break;
			}
		} else if (nodeType == XML_READER_TYPE_ELEMENT) {
			if (geo3dml::IsiEqual(localName, elemName)) {
				++iteratorLevel;
			}
		}
		status = xmlTextReaderRead(reader);
	}
	if (status != 1) {
		std::string err = XMLReaderHelper::FormatErrorMessageWithPosition(reader, "missing end element of " + elemName);
		SetStatus(false, err);
	}
	return IsOK();
}
