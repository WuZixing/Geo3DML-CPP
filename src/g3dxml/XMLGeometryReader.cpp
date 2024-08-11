#include <g3dxml/XMLGeometryReader.h>
#include <g3dxml/XMLTINReader.h>
#include <g3dxml/XMLCornerPointGridReader.h>
#include <g3dxml/XMLGeoDiscreteCoverageReader.h>
#include <g3dxml/XMLLineStringReader.h>
#include <g3dxml/XMLPointReader.h>
#include <g3dxml/XMLMultiPointReader.h>
#include <g3dxml/XMLAnnotationReader.h>
#include <g3dxml/XMLTriangularPrismVolumeReader.h>
#include <g3dxml/XMLRectifiedGridReader.h>
#include <g3dxml/XMLTetrahedronVolumeReader.h>
#include <g3dxml/XMLCuboidVolumeReader.h>
#include <g3dxml/XMLTruncatedRegularGridReader.h>
#include <geo3dml/Utils.h>

using namespace g3dxml;

const std::string XMLGeometryReader::Element = "Geometry";
const std::string XMLGeometryReader::Element_Shape = "Shape";
const std::string XMLGeometryReader::Element_ShapeProperty = "ShapeProperty";

XMLGeometryReader::XMLGeometryReader(geo3dml::ObjectFactory* factory) {
	g3dFactory_ = factory;
}

XMLGeometryReader::~XMLGeometryReader() {
	g3dFactory_ = nullptr;
}

geo3dml::Geometry* XMLGeometryReader::ReadGeometry(xmlTextReaderPtr reader) {
	geo3dml::Geometry* geometry = nullptr;
	int status = xmlTextReaderRead(reader);
	while (status == 1) {
		const char* localName = (const char*)xmlTextReaderConstLocalName(reader);
		int nodeType = xmlTextReaderNodeType(reader);
		if (nodeType == XML_READER_TYPE_END_ELEMENT && geo3dml::IsiEqual(localName, Element)) {
			break;
		} else if (nodeType == XML_READER_TYPE_ELEMENT) {
			if (geo3dml::IsiEqual(localName, Element_Shape)) {
				geometry = ReadShape(reader);
			} else if (geo3dml::IsiEqual(localName, Element_ShapeProperty)) {
				if (geometry != nullptr) {
					// Shape object must be available before reading shape property.
					ReadShapeProperty(reader, geometry);
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
				}
			} else if (geo3dml::IsiEqual(localName, XMLCornerPointGridReader::Element)) {
				XMLCornerPointGridReader gridReader(g3dFactory_);
				geo = gridReader.ReadCornerPointGrid(reader);
				if (geo == nullptr) {
					SetStatus(false, gridReader.Error());
				}
			} else if (geo3dml::IsiEqual(localName, XMLLineStringReader::Element)) {
				XMLLineStringReader lineStringReader(g3dFactory_);
				geo = lineStringReader.ReadLineString(reader);
				if (geo == nullptr) {
					SetStatus(false, lineStringReader.Error());
				}
			} else if (geo3dml::IsiEqual(localName, XMLPointReader::Element)) {
				XMLPointReader pointReader(g3dFactory_);
				geo = pointReader.ReadPoint(reader);
				if (geo == nullptr) {
					SetStatus(false, pointReader.Error());
				}
			} else if (geo3dml::IsiEqual(localName, XMLMultiPointReader::Element)) {
				XMLMultiPointReader mPointReader(g3dFactory_);
				geo = mPointReader.ReadMultiPoint(reader);
				if (geo == nullptr) {
					SetStatus(false, mPointReader.Error());
				}
			} else if (geo3dml::IsiEqual(localName, XMLAnnotationReader::Element)) {
				XMLAnnotationReader annotationReader(g3dFactory_);
				geo = annotationReader.ReadAnnotation(reader);
				if (geo == nullptr) {
					SetStatus(false, annotationReader.Error());
				}
			} else if (geo3dml::IsiEqual(localName, XMLTriangularPrismVolumeReader::Element)) {
				XMLTriangularPrismVolumeReader gtpReader(g3dFactory_);
				geo = gtpReader.ReadVolume(reader);
				if (geo == nullptr) {
					SetStatus(false, gtpReader.Error());
				}
			} else if (geo3dml::IsiEqual(localName, XMLRectifiedGridReader::Element)) {
				XMLRectifiedGridReader gridReader(g3dFactory_);
				geo = gridReader.ReadGrid(reader);
				if (geo == nullptr) {
					SetStatus(false, gridReader.Error());
				}
			} else if (geo3dml::IsiEqual(localName, XMLTetrahedronVolumeReader::Element)) {
				XMLTetrahedronVolumeReader tetraReader(g3dFactory_);
				geo = tetraReader.ReadTetrahedronVolume(reader);
				if (geo == nullptr) {
					SetStatus(false, tetraReader.Error());
				}
			} else if (geo3dml::IsiEqual(localName, XMLCuboidVolumeReader::Element)) {
				XMLCuboidVolumeReader cuboidReader(g3dFactory_);
				geo = cuboidReader.ReadCuboidVolume(reader);
				if (geo == nullptr) {
					SetStatus(false, cuboidReader.Error());
				}
			} else if (geo3dml::IsiEqual(localName, XMLTruncatedRegularGridReader::Element)) {
				XMLTruncatedRegularGridReader trGridReader(g3dFactory_);
				geo = trGridReader.ReadGrid(reader);
				if (geo == nullptr) {
					SetStatus(false, trGridReader.Error());
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
