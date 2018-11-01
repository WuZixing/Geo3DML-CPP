#include <g3dxml/XMLGeometryReader.h>
#include <g3dxml/XMLTINReader.h>
#include <g3dxml/XMLCornerPointGridReader.h>
#include <g3dxml/XMLUniformGridReader.h>
#include <g3dxml/XMLGeoDiscreteCoverageReader.h>
#include <g3dxml/XMLLineStringReader.h>
#include <g3dxml/XMLPointReader.h>

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
	geo3dml::Geometry* geometry = g3dFactory_->NewGeometry();
	geometry->SetName(XMLReaderHelper::Attribute(reader, "Name"));
	std::string lod = XMLReaderHelper::Attribute(reader, "LOD");
	geometry->SetLODLevel(strtol(lod.c_str(), NULL, 10));
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
				geo3dml::Shape* shape = ReadShape(reader);
				if (shape != NULL) {
					geo3dml::Shape* s = geometry->SetShape(shape);
					if (s != NULL) {
						delete s;
					}
				} else {
					break;
				}
			} else if (_stricmp(localName, Element_ShapeProperty.c_str()) == 0) {
				geo3dml::Shape* shape = geometry->GetShape();
				if (shape == NULL) {
					std::string err = XMLReaderHelper::FormatErrorMessageWithPosition(reader, "Shape object must be available before reading shape property.");
					SetStatus(false, err);
				} else {
					if (!ReadShapeProperty(reader, shape)) {
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

geo3dml::Shape* XMLGeometryReader::ReadShape(xmlTextReaderPtr reader) {
	geo3dml::Shape* shape = NULL;
	int status = xmlTextReaderRead(reader);
	while (status == 1) {
		const char* localName = (const char*)xmlTextReaderConstLocalName(reader);
		int nodeType = xmlTextReaderNodeType(reader);
		if (nodeType == XML_READER_TYPE_END_ELEMENT && _stricmp(localName, Element_Shape.c_str()) == 0) {
			break;
		} else if (nodeType == XML_READER_TYPE_ELEMENT) {
			/// TODO: read concrete shape objects.
			if (_stricmp(localName, XMLTINReader::Element.c_str()) == 0) {
				XMLTINReader tinReader(g3dFactory_);
				shape = tinReader.ReadTIN(reader);
				if (shape == NULL) {
					SetStatus(false, tinReader.Error());
					break;
				}
			} else if (_stricmp(localName, XMLCornerPointGridReader::Element.c_str()) == 0) {
				XMLCornerPointGridReader gridReader(g3dFactory_);
				shape = gridReader.ReadCornerPointGrid(reader);
				if (shape == NULL) {
					SetStatus(false, gridReader.Error());
					break;
				}
			} else if (_stricmp(localName, XMLUniformGridReader::Element.c_str()) == 0) {
				XMLUniformGridReader gridReader(g3dFactory_);
				shape = gridReader.ReadUniformGrid(reader);
				if (shape == NULL) {
					SetStatus(false, gridReader.Error());
					break;
				}
			} else if (_stricmp(localName, XMLLineStringReader::Element.c_str()) == 0) {
				XMLLineStringReader lineStringReader(g3dFactory_);
				shape = lineStringReader.ReadLineString(reader);
				if (shape == NULL) {
					SetStatus(false, lineStringReader.Error());
					break;
				}
			} else if (_stricmp(localName, XMLPointReader::Element.c_str()) == 0) {
				XMLPointReader pointReader(g3dFactory_);
				shape = pointReader.ReadPoint(reader);
				if (shape == NULL) {
					SetStatus(false, pointReader.Error());
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
	if (!IsOK() && shape != NULL) {
		delete shape;
		shape = NULL;
	}
	return shape;
}

bool XMLGeometryReader::ReadShapeProperty(xmlTextReaderPtr reader, geo3dml::Shape* toShape) {
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
