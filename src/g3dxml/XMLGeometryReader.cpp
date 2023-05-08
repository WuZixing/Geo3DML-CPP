#include <g3dxml/XMLGeometryReader.h>
#include <g3dxml/XMLTINReader.h>
#include <g3dxml/XMLCornerPointGridReader.h>
#include <g3dxml/XMLUniformGridReader.h>
#include <g3dxml/XMLGeoDiscreteCoverageReader.h>
#include <g3dxml/XMLLineStringReader.h>
#include <g3dxml/XMLPointReader.h>
#include <g3dxml/XMLMultiPointReader.h>
#include <g3dxml/XMLAnnotationReader.h>
#include <g3dxml/XMLGTPVolumeReader.h>
#include <geo3dml/Utils.h>

using namespace g3dxml;

std::string XMLGeometryReader::Element = "Geometry";
std::string XMLGeometryReader::Element_Shape = "Shape";
std::string XMLGeometryReader::Element_ShapeProperty = "ShapeProperty";

XMLGeometryReader::XMLGeometryReader(geo3dml::ObjectFactory* factory) {
	g3dFactory_ = factory;
}

XMLGeometryReader::~XMLGeometryReader() {
	g3dFactory_ = nullptr;
}

geo3dml::Geometry* XMLGeometryReader::ReadGeometry(xmlTextReaderPtr reader) {
	geo3dml::Geometry* geometry = nullptr;
	std::string geoName = XMLReaderHelper::Attribute(reader, "Name");
	std::string geoLOD = XMLReaderHelper::Attribute(reader, "LOD");
	bool metEndElement = false;
	int status = xmlTextReaderRead(reader);
	while (status == 1) {
		const char* localName = (const char*)xmlTextReaderConstLocalName(reader);
		int nodeType = xmlTextReaderNodeType(reader);
		if (nodeType == XML_READER_TYPE_END_ELEMENT && geo3dml::IsiEqual(localName, Element)) {
			metEndElement = true;
			break;
		} else if (nodeType == XML_READER_TYPE_ELEMENT) {
			if (geo3dml::IsiEqual(localName, Element_Shape)) {
				geometry = ReadShape(reader);
				if (geometry != nullptr) {
					geometry->SetName(geoName);
					geometry->SetLODLevel(strtol(geoLOD.c_str(), nullptr, 10));
				} else {
					break;
				}
			} else if (geo3dml::IsiEqual(localName, Element_ShapeProperty)) {
				if (geometry == nullptr) {
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
		geometry = nullptr;
	}
	return geometry;
}

geo3dml::Geometry* XMLGeometryReader::ReadShape(xmlTextReaderPtr reader) {
	geo3dml::Geometry* geo = nullptr;
	int status = xmlTextReaderRead(reader);
	while (status == 1) {
		const char* localName = (const char*)xmlTextReaderConstLocalName(reader);
		int nodeType = xmlTextReaderNodeType(reader);
		if (nodeType == XML_READER_TYPE_END_ELEMENT && geo3dml::IsiEqual(localName, Element_Shape)) {
			break;
		} else if (nodeType == XML_READER_TYPE_ELEMENT) {
			if (geo3dml::IsiEqual(localName, XMLTINReader::Element)) {
				XMLTINReader tinReader(g3dFactory_);
				geo = tinReader.ReadTIN(reader);
				if (geo == nullptr) {
					SetStatus(false, tinReader.Error());
					break;
				}
			} else if (geo3dml::IsiEqual(localName, XMLCornerPointGridReader::Element)) {
				XMLCornerPointGridReader gridReader(g3dFactory_);
				geo = gridReader.ReadCornerPointGrid(reader);
				if (geo == nullptr) {
					SetStatus(false, gridReader.Error());
					break;
				}
			} else if (geo3dml::IsiEqual(localName, XMLUniformGridReader::Element)) {
				XMLUniformGridReader gridReader(g3dFactory_);
				geo = gridReader.ReadUniformGrid(reader);
				if (geo == nullptr) {
					SetStatus(false, gridReader.Error());
					break;
				}
			} else if (geo3dml::IsiEqual(localName, XMLLineStringReader::Element)) {
				XMLLineStringReader lineStringReader(g3dFactory_);
				geo = lineStringReader.ReadLineString(reader);
				if (geo == nullptr) {
					SetStatus(false, lineStringReader.Error());
					break;
				}
			} else if (geo3dml::IsiEqual(localName, XMLPointReader::Element)) {
				XMLPointReader pointReader(g3dFactory_);
				geo = pointReader.ReadPoint(reader);
				if (geo == nullptr) {
					SetStatus(false, pointReader.Error());
					break;
				}
			} else if (geo3dml::IsiEqual(localName, XMLMultiPointReader::Element)) {
				XMLMultiPointReader mPointReader(g3dFactory_);
				geo = mPointReader.ReadMultiPoint(reader);
				if (geo == nullptr) {
					SetStatus(false, mPointReader.Error());
					break;
				}
			} else if (geo3dml::IsiEqual(localName, XMLAnnotationReader::Element)) {
				XMLAnnotationReader annotationReader(g3dFactory_);
				geo = annotationReader.ReadAnnotation(reader);
				if (geo == nullptr) {
					SetStatus(false, annotationReader.Error());
					break;
				}
			} else if (geo3dml::IsiEqual(localName, XMLGTPVolumeReader::Element)) {
				XMLGTPVolumeReader gtpReader(g3dFactory_);
				geo = gtpReader.ReadVolume(reader);
				if (geo == nullptr) {
					SetStatus(false, gtpReader.Error());
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
	if (!IsOK() && geo != nullptr) {
		delete geo;
		geo = nullptr;
	}
	return geo;
}

bool XMLGeometryReader::ReadShapeProperty(xmlTextReaderPtr reader, geo3dml::Geometry* toShape) {
	int status = xmlTextReaderRead(reader);
	while (status == 1) {
		const char* localName = (const char*)xmlTextReaderConstLocalName(reader);
		int nodeType = xmlTextReaderNodeType(reader);
		if (nodeType == XML_READER_TYPE_END_ELEMENT && geo3dml::IsiEqual(localName, Element_ShapeProperty)) {
			break;
		} else if (nodeType == XML_READER_TYPE_ELEMENT) {
			if (geo3dml::IsiEqual(localName, XMLGeoDiscreteCoverageReader::Element)) {
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
