#include <g3dxml/XMLSurfaceSymbolizerReader.h>
#include <g3dxml/XMLMaterialReader.h>
#include <g3dxml/XMLPointSymbolizerReader.h>
#include <g3dxml/XMLLineSymbolizerReader.h>

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
		if (nodeType == XML_READER_TYPE_END_ELEMENT && _stricmp(localName, Element.c_str()) == 0) {
			break;
		} else if (nodeType == XML_READER_TYPE_ELEMENT) {
			if (_stricmp(localName, Element_Front.c_str()) == 0) {
				if (!ReadFront(reader, surfaceSym)) {
					break;
				}
			} else if (_stricmp(localName, Element_Back.c_str()) == 0) {
				if (!ReadBack(reader, surfaceSym)) {
					break;
				}
			} else if (_stricmp(localName, Element_Vertex.c_str()) == 0) {
				if (!ReadVertex(reader, surfaceSym)) {
					break;
				}
			} else if (_stricmp(localName, Element_Frame.c_str()) == 0) {
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
		if (nodeType == XML_READER_TYPE_END_ELEMENT && _stricmp(localName, Element_Front.c_str()) == 0) {
			break;
		} else if (nodeType == XML_READER_TYPE_ELEMENT) {
			if (_stricmp(localName, XMLMaterialReader::Element.c_str()) == 0) {
				geo3dml::Material material;
				XMLMaterialReader materialReader(g3dFactory_);
				if (materialReader.ReadMaterial(reader, material)) {
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
		if (nodeType == XML_READER_TYPE_END_ELEMENT && _stricmp(localName, Element_Back.c_str()) == 0) {
			break;
		} else if (nodeType == XML_READER_TYPE_ELEMENT) {
			if (_stricmp(localName, XMLMaterialReader::Element.c_str()) == 0) {
				geo3dml::Material material;
				XMLMaterialReader materialReader(g3dFactory_);
				if (materialReader.ReadMaterial(reader, material)) {
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
		if (nodeType == XML_READER_TYPE_END_ELEMENT && _stricmp(localName, Element_Vertex.c_str()) == 0) {
			break;
		} else if (nodeType == XML_READER_TYPE_ELEMENT) {
			if (_stricmp(localName, XMLPointSymbolizerReader::Element.c_str()) == 0) {
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
		if (nodeType == XML_READER_TYPE_END_ELEMENT && _stricmp(localName, Element_Frame.c_str()) == 0) {
			break;
		} else if (nodeType == XML_READER_TYPE_ELEMENT) {
			if (_stricmp(localName, XMLLineSymbolizerReader::Element.c_str()) == 0) {
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
