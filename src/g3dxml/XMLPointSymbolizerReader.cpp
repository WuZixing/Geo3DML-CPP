#include <g3dxml/XMLPointSymbolizerReader.h>
#include <g3dxml/XMLMaterialReader.h>
#include <geo3dml/Utils.h>

using namespace g3dxml;

std::string XMLPointSymbolizerReader::Element = "GeoPointSymbolizer";

XMLPointSymbolizerReader::XMLPointSymbolizerReader(geo3dml::ObjectFactory* factory) : Element_Graphic("Graphic") {
	g3dFactory_ = factory;
}

XMLPointSymbolizerReader::~XMLPointSymbolizerReader() {
	g3dFactory_ = NULL;
}

geo3dml::PointSymbolizer* XMLPointSymbolizerReader::ReadPointSym(xmlTextReaderPtr reader) {
	geo3dml::PointSymbolizer* pointSym = g3dFactory_->NewPointSymbolizer();
	int status = xmlTextReaderRead(reader);
	while (status == 1) {
		const char* localName = (const char*)xmlTextReaderConstLocalName(reader);
		int nodeType = xmlTextReaderNodeType(reader);
		if (nodeType == XML_READER_TYPE_END_ELEMENT && geo3dml::IsiEqual(localName, Element)) {
			break;
		} else if (nodeType == XML_READER_TYPE_ELEMENT) {
			if (geo3dml::IsiEqual(localName, Element_Graphic)) {
				if (!ReadGraphic(reader, pointSym)) {
					break;
				}
			} else if (geo3dml::IsiEqual(localName, XMLMaterialReader::Element)) {
				XMLMaterialReader materialReader(g3dFactory_);
				geo3dml::Material material;
				if (materialReader.ReadMaterial(reader, material)) {
					pointSym->SetMaterial(material);
				} else {
					SetStatus(false, materialReader.Error());
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
		delete pointSym;
		pointSym = NULL;
	}
	return pointSym;
}

bool XMLPointSymbolizerReader::ReadGraphic(xmlTextReaderPtr reader, geo3dml::PointSymbolizer* toPointSym) {
	int status = xmlTextReaderRead(reader);
	while (status == 1) {
		const char* localName = (const char*)xmlTextReaderConstLocalName(reader);
		int nodeType = xmlTextReaderNodeType(reader);
		if (nodeType == XML_READER_TYPE_END_ELEMENT && geo3dml::IsiEqual(localName, Element_Graphic)) {
			break;
		} else if (nodeType == XML_READER_TYPE_ELEMENT) {
			if (geo3dml::IsiEqual(localName, "Size")) {
				std::string v;
				if (!XMLReaderHelper::TextNode(reader, "Size", v)) {
					SetStatus(false, v);
					break;
				}
				toPointSym->SetSize(strtof(v.c_str(), NULL));
			}
		}
		status = xmlTextReaderRead(reader);
	}
	if (status != 1) {
		std::string err = XMLReaderHelper::FormatErrorMessageWithPosition(reader, "missing end element of " + Element_Graphic);
		SetStatus(false, err);
	}
	return IsOK();
}
