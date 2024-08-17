#include <g3dxml/XMLSurfaceSymbolizerReader.h>
#include <g3dxml/XMLMaterialReader.h>
#include <g3dxml/XMLPointSymbolizerReader.h>
#include <g3dxml/XMLLineSymbolizerReader.h>
#include <geo3dml/Utils.h>

using namespace g3dxml;

std::string XMLSurfaceSymbolizerReader::Element = "GeoSurfaceSymbolizer";

XMLSurfaceSymbolizerReader::XMLSurfaceSymbolizerReader(geo3dml::ObjectFactory* factory) :
	Element_Front("Front"),
	Element_Back("Back"),
	Element_Vertex("VertexSymbolizer"),
	Element_Frame("FrameSymbolizer") {
	g3dFactory_ = factory;
}

XMLSurfaceSymbolizerReader::~XMLSurfaceSymbolizerReader() {
	g3dFactory_ = NULL;
}

geo3dml::SurfaceSymbolizer* XMLSurfaceSymbolizerReader::ReadSurfaceSym(xmlTextReaderPtr reader) {
	geo3dml::SurfaceSymbolizer* surfaceSym = g3dFactory_->NewSurfaceSymbolizer();
	surfaceSym->EnableBackRender(false);
	surfaceSym->EnableVertexRender(false);
	surfaceSym->EnableFrameRender(false);
	int status = xmlTextReaderRead(reader);
	while (status == 1) {
		const char* localName = (const char*)xmlTextReaderConstLocalName(reader);
		int nodeType = xmlTextReaderNodeType(reader);
		if (nodeType == XML_READER_TYPE_END_ELEMENT && geo3dml::IsiEqual(localName, Element)) {
			break;
		} else if (nodeType == XML_READER_TYPE_ELEMENT) {
			if (geo3dml::IsiEqual(localName, Element_Front)) {
				if (!ReadFront(reader, surfaceSym)) {
					break;
				}
			} else if (geo3dml::IsiEqual(localName, Element_Back)) {
				if (!ReadBack(reader, surfaceSym)) {
					break;
				}
			} else if (geo3dml::IsiEqual(localName, Element_Vertex)) {
				if (!ReadVertex(reader, surfaceSym)) {
					break;
				}
			} else if (geo3dml::IsiEqual(localName, Element_Frame)) {
				if (!ReadFrame(reader, surfaceSym)) {
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
		delete surfaceSym;
		surfaceSym = NULL;
	}
	return surfaceSym;
}

bool XMLSurfaceSymbolizerReader::ReadFront(xmlTextReaderPtr reader, geo3dml::SurfaceSymbolizer* toSurfaceSym) {
	int status = xmlTextReaderRead(reader);
	while (status == 1) {
		const char* localName = (const char*)xmlTextReaderConstLocalName(reader);
		int nodeType = xmlTextReaderNodeType(reader);
		if (nodeType == XML_READER_TYPE_END_ELEMENT && geo3dml::IsiEqual(localName, Element_Front)) {
			break;
		} else if (nodeType == XML_READER_TYPE_ELEMENT) {
			if (geo3dml::IsiEqual(localName, XMLMaterialReader::Element) || geo3dml::IsiEqual(localName, XMLMaterialReader::Element_PBRMaterial)) {
				geo3dml::PBRMaterial material;
				XMLMaterialReader materialReader;
				if (materialReader.ReadMaterial(reader, localName, material)) {
					toSurfaceSym->SetFrontMaterial(material);
				} else {
					SetStatus(false, materialReader.Error());
					break;
				}
			}
		}
		status = xmlTextReaderRead(reader);
	}
	if (status != 1) {
		std::string err = XMLReaderHelper::FormatErrorMessageWithPosition(reader, "missing end element of " + Element_Front);
		SetStatus(false, err);
	}
	return IsOK();
}

bool XMLSurfaceSymbolizerReader::ReadBack(xmlTextReaderPtr reader, geo3dml::SurfaceSymbolizer* toSurfaceSym) {
	int status = xmlTextReaderRead(reader);
	while (status == 1) {
		const char* localName = (const char*)xmlTextReaderConstLocalName(reader);
		int nodeType = xmlTextReaderNodeType(reader);
		if (nodeType == XML_READER_TYPE_END_ELEMENT && geo3dml::IsiEqual(localName, Element_Back)) {
			break;
		} else if (nodeType == XML_READER_TYPE_ELEMENT) {
			if (geo3dml::IsiEqual(localName, XMLMaterialReader::Element) || geo3dml::IsiEqual(localName, XMLMaterialReader::Element_PBRMaterial)) {
				geo3dml::PBRMaterial material;
				XMLMaterialReader materialReader;
				if (materialReader.ReadMaterial(reader, localName, material)) {
					toSurfaceSym->SetBackMaterial(material);
				} else {
					SetStatus(false, materialReader.Error());
					break;
				}
			}
		}
		status = xmlTextReaderRead(reader);
	}
	if (status != 1) {
		std::string err = XMLReaderHelper::FormatErrorMessageWithPosition(reader, "missing end element of " + Element_Back);
		SetStatus(false, err);
	}
	return IsOK();
}

bool XMLSurfaceSymbolizerReader::ReadVertex(xmlTextReaderPtr reader, geo3dml::SurfaceSymbolizer* toSurfaceSym) {
	int status = xmlTextReaderRead(reader);
	while (status == 1) {
		const char* localName = (const char*)xmlTextReaderConstLocalName(reader);
		int nodeType = xmlTextReaderNodeType(reader);
		if (nodeType == XML_READER_TYPE_END_ELEMENT && geo3dml::IsiEqual(localName, Element_Vertex)) {
			break;
		} else if (nodeType == XML_READER_TYPE_ELEMENT) {
			if (geo3dml::IsiEqual(localName, XMLPointSymbolizerReader::Element)) {
				XMLPointSymbolizerReader pointSymReader(g3dFactory_);
				geo3dml::PointSymbolizer* pointSym = pointSymReader.ReadPointSym(reader);
				if (pointSym != NULL) {
					toSurfaceSym->SetVertexSymbolizer(pointSym);
					toSurfaceSym->EnableVertexRender(true);
				} else {
					SetStatus(false, pointSymReader.Error());
					break;
				}
			}
		}
		status = xmlTextReaderRead(reader);
	}
	if (status != 1) {
		std::string err = XMLReaderHelper::FormatErrorMessageWithPosition(reader, "missing end element of " + Element_Vertex);
		SetStatus(false, err);
	}
	return IsOK();
}

bool XMLSurfaceSymbolizerReader::ReadFrame(xmlTextReaderPtr reader, geo3dml::SurfaceSymbolizer* toSurfaceSym) {
	int status = xmlTextReaderRead(reader);
	while (status == 1) {
		const char* localName = (const char*)xmlTextReaderConstLocalName(reader);
		int nodeType = xmlTextReaderNodeType(reader);
		if (nodeType == XML_READER_TYPE_END_ELEMENT && geo3dml::IsiEqual(localName, Element_Frame)) {
			break;
		} else if (nodeType == XML_READER_TYPE_ELEMENT) {
			if (geo3dml::IsiEqual(localName, XMLLineSymbolizerReader::Element)) {
				XMLLineSymbolizerReader lineSymReader(g3dFactory_);
				geo3dml::LineSymbolizer* lineSym = lineSymReader.ReadLineSym(reader);
				if (lineSym != NULL) {
					toSurfaceSym->SetFrameSymbolizer(lineSym);
					toSurfaceSym->EnableFrameRender(true);
				} else {
					SetStatus(false, lineSymReader.Error());
					break;
				}
			}
		}
		status = xmlTextReaderRead(reader);
	}
	if (status != 1) {
		std::string err = XMLReaderHelper::FormatErrorMessageWithPosition(reader, "missing end element of " + Element_Frame);
		SetStatus(false, err);
	}
	return IsOK();
}
