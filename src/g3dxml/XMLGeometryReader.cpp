#include <g3dxml/XMLGeometryReader.h>
#include <g3dxml/XMLTINReader.h>
#include <g3dxml/XMLCornerPointGridReader.h>
#include <g3dxml/XMLUniformGridReader.h>
#include <g3dxml/XMLGeoDiscreteCoverageReader.h>
#include <g3dxml/XMLLineStringReader.h>
#include <g3dxml/XMLPointReader.h>
#include <g3dxml/XMLMultiPointReader.h>

using namespace g3dxml;

std::string XMLGeometryReader::Element = "Geometry";
std::string XMLGeometryReader::Element_Shape = "Shape";
std::string XMLGeometryReader::Element_ShapeProperty = "ShapeProperty";

XMLGeometryReader::XMLGeometryReader(geo3dml::ObjectFactory* factory) {
	g3dFactory_ = factory;
}

XMLGeometryReader::~XMLGeometryReader() {
	g3dFactory_ = NULL;
}

geo3dml::Geometry* XMLGeometryReader::ReadGeometry(xmlTextReaderPtr reader) {
	geo3dml::Geometry* geometry = NULL;
	std::string geoName = XMLReaderHelper::Attribute(reader, "Name");
	std::string geoLOD = XMLReaderHelper::Attribute(reader, "LOD");
	bool metEndElement = false;
	int status = xmlTextReaderRead(reader);
	while (status == 1) {
		const char* localName = (const char*)xmlTextReaderConstLocalName(reader);
		int nodeType = xmlTextReaderNodeType(reader);
		if (nodeType == XML_READER_TYPE_END_ELEMENT && _stricmp(localName, Element.c_str()) == 0) {
			metEndElement = true;
			break;
		} else if (nodeType == XML_READER_TYPE_ELEMENT) {
			if (_stricmp(localName, Element_Shape.c_str()) == 0) {
				geometry = ReadShape(reader);
				if (geometry != NULL) {
					geometry->SetName(geoName);
					geometry->SetLODLevel(strtol(geoLOD.c_str(), NULL, 10));
				} else {
					break;
				}
			} else if (_stricmp(localName, Element_ShapeProperty.c_str()) == 0) {
				if (geometry == NULL) {
					std::string err = XMLReaderHelper::FormatErrorMessageWithPosition(reader, "Shape object must be available before reading shape property.");
					SetStatus(false, err);
				} else {
					if (!ReadShapeProperty(reader, geometry)) {
						break;
					}
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
		delete geometry;
		geometry = NULL;
	}
	return geometry;
}

geo3dml::Geometry* XMLGeometryReader::ReadShape(xmlTextReaderPtr reader) {
	geo3dml::Geometry* geo = NULL;
	int status = xmlTextReaderRead(reader);
	while (status == 1) {
		const char* localName = (const char*)xmlTextReaderConstLocalName(reader);
		int nodeType = xmlTextReaderNodeType(reader);
		if (nodeType == XML_READER_TYPE_END_ELEMENT && _stricmp(localName, Element_Shape.c_str()) == 0) {
			break;
		} else if (nodeType == XML_READER_TYPE_ELEMENT) {
			if (_stricmp(localName, XMLTINReader::Element.c_str()) == 0) {
				XMLTINReader tinReader(g3dFactory_);
				geo = tinReader.ReadTIN(reader);
				if (geo == NULL) {
					SetStatus(false, tinReader.Error());
					break;
				}
			} else if (_stricmp(localName, XMLCornerPointGridReader::Element.c_str()) == 0) {
				XMLCornerPointGridReader gridReader(g3dFactory_);
				geo = gridReader.ReadCornerPointGrid(reader);
				if (geo == NULL) {
					SetStatus(false, gridReader.Error());
					break;
				}
			} else if (_stricmp(localName, XMLUniformGridReader::Element.c_str()) == 0) {
				XMLUniformGridReader gridReader(g3dFactory_);
				geo = gridReader.ReadUniformGrid(reader);
				if (geo == NULL) {
					SetStatus(false, gridReader.Error());
					break;
				}
			} else if (_stricmp(localName, XMLLineStringReader::Element.c_str()) == 0) {
				XMLLineStringReader lineStringReader(g3dFactory_);
				geo = lineStringReader.ReadLineString(reader);
				if (geo == NULL) {
					SetStatus(false, lineStringReader.Error());
					break;
				}
			} else if (_stricmp(localName, XMLPointReader::Element.c_str()) == 0) {
				XMLPointReader pointReader(g3dFactory_);
				geo = pointReader.ReadPoint(reader);
				if (geo == NULL) {
					SetStatus(false, pointReader.Error());
					break;
				}
			} else if (_stricmp(localName, XMLMultiPointReader::Element.c_str()) == 0) {
				XMLMultiPointReader mPointReader(g3dFactory_);
				geo = mPointReader.ReadMultiPoint(reader);
				if (geo == NULL) {
					SetStatus(false, mPointReader.Error());
					break;
				}
			}
		}
		status = xmlTextReaderRead(reader);
	}
	if (status != 1) {
		std::string err = XMLReaderHelper::FormatErrorMessageWithPosition(reader, "missing end element of " + Element_Shape);
		SetStatus(false, err);
	}
	if (!IsOK() && geo != NULL) {
		delete geo;
		geo = NULL;
	}
	return geo;
}

bool XMLGeometryReader::ReadShapeProperty(xmlTextReaderPtr reader, geo3dml::Geometry* toShape) {
	int status = xmlTextReaderRead(reader);
	while (status == 1) {
		const char* localName = (const char*)xmlTextReaderConstLocalName(reader);
		int nodeType = xmlTextReaderNodeType(reader);
		if (nodeType == XML_READER_TYPE_END_ELEMENT && _stricmp(localName, Element_ShapeProperty.c_str()) == 0) {
			break;
		} else if (nodeType == XML_READER_TYPE_ELEMENT) {
			if (_stricmp(localName, XMLGeoDiscreteCoverageReader::Element.c_str()) == 0) {
				XMLGeoDiscreteCoverageReader coverageReader(g3dFactory_);
				if (!coverageReader.ReadGeoDiscreteCoverage(reader, toShape)) {
					SetStatus(false, coverageReader.Error());
					break;
				}
			}
		}
		status = xmlTextReaderRead(reader);
	}
	if (status != 1) {
		std::string err = XMLReaderHelper::FormatErrorMessageWithPosition(reader, "missing end element of " + Element_ShapeProperty);
		SetStatus(false, err);
	}
	return IsOK();
}
