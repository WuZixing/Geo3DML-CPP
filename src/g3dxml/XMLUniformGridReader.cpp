#include <g3dxml/XMLUniformGridReader.h>
#include <geo3dml/Utils.h>

using namespace g3dxml;

const std::string XMLUniformGridReader::Element = "GeoUniformGrid";

XMLUniformGridReader::XMLUniformGridReader(geo3dml::ObjectFactory* factory) {
	g3dFactory_ = factory;
}

XMLUniformGridReader::~XMLUniformGridReader() {

}

geo3dml::UniformGrid* XMLUniformGridReader::ReadUniformGrid(xmlTextReaderPtr reader) {
	geo3dml::UniformGrid* grid = NULL;
	std::string id = XMLReaderHelper::AttributeGMLID(reader);
	unsigned char flag = 0;
	double originX = 0, originY = 0, originZ = 0;
	double stepX = 0, stepY = 0, stepZ = 0;
	int dimI = 1, dimJ = 1, dimK = 1;
	int status = xmlTextReaderRead(reader);
	while (status == 1) {
		const char* localName = (const char*)xmlTextReaderConstLocalName(reader);
		int nodeType = xmlTextReaderNodeType(reader);
		if (nodeType == XML_READER_TYPE_END_ELEMENT && geo3dml::IsiEqual(localName, Element)) {
			break;
		} else if (nodeType == XML_READER_TYPE_ELEMENT) {
			if (geo3dml::IsiEqual(localName, Element_Origin)) {
				std::string origin;
				if (!XMLReaderHelper::TextNode(reader, Element_Origin, origin)) {
					SetStatus(false, origin);
					break;
				}
				char* end = NULL;
				originX = strtod(origin.c_str(), &end);
				originY = strtod(end, &end);
				originZ = strtod(end, NULL);
				flag |= 0x01;
			} else if (geo3dml::IsiEqual(localName, Element_Steps)) {
				std::string steps;
				if (!XMLReaderHelper::TextNode(reader, Element_Steps, steps)) {
					SetStatus(false, steps);
					break;
				}
				char* end = NULL;
				stepX = strtod(steps.c_str(), &end);
				stepY = strtod(end, &end);
				stepZ = strtod(end, &end);
				flag |= 0x02;
			} else if (geo3dml::IsiEqual(localName, Element_Dimension)) {
				std::string dims;
				if (!XMLReaderHelper::TextNode(reader, Element_Dimension, dims)) {
					SetStatus(false, dims);
					break;
				}
				char* end = NULL;
				dimI = strtol(dims.c_str(), &end, 10);
				dimJ = strtol(end, &end, 10);
				dimK = strtol(end, NULL, 10);
				flag |= 0x04;
			} else if (geo3dml::IsiEqual(localName, Element_Cells)) {
				if (!ReadCells(reader, grid)) {
					break;
				}
			}
		}
		if (flag == 0x07 && grid == NULL) {
			grid = g3dFactory_->NewUniformGrid(originX, originY, originZ, stepX, stepY, stepZ, dimI, dimJ, dimK);
			grid->SetID(id);
		}
		status = xmlTextReaderRead(reader);
	}
	if (status != 1) {
		std::string err = XMLReaderHelper::FormatErrorMessageWithPosition(reader, "missing end element of " + Element);
		SetStatus(false, err);
	}
	if (!IsOK() && grid != NULL) {
		delete grid;
		grid = NULL;
	}
	return grid;
}

bool XMLUniformGridReader::ReadCells(xmlTextReaderPtr reader, geo3dml::UniformGrid* grid) {
	if (grid == NULL) {
		std::string err = XMLReaderHelper::FormatErrorMessageWithPosition(reader, "invalid geo3dml::UniformGrid object for reading cells");
		SetStatus(false, err);
		return false;
	}
	int status = xmlTextReaderRead(reader);
	while (status == 1) {
		const char* localName = (const char*)xmlTextReaderConstLocalName(reader);
		int nodeType = xmlTextReaderNodeType(reader);
		if (nodeType == XML_READER_TYPE_END_ELEMENT && geo3dml::IsiEqual(localName, Element_Cells)) {
			break;
		} else if (nodeType == XML_READER_TYPE_ELEMENT) {
			if (geo3dml::IsiEqual(localName, Element_Cell)) {
				if (!ReadCell(reader, grid)) {
					break;
				}
			}
		}
		status = xmlTextReaderRead(reader);
	}
	if (status != 1) {
		std::string err = XMLReaderHelper::FormatErrorMessageWithPosition(reader, "missing end element of " + Element_Cells);
		SetStatus(false, err);
	}
	return IsOK();
}

bool XMLUniformGridReader::ReadCell(xmlTextReaderPtr reader, geo3dml::UniformGrid* grid) {
	std::string attr = XMLReaderHelper::Attribute(reader, "I");
	int i = strtol(attr.c_str(), NULL, 10);
	attr = XMLReaderHelper::Attribute(reader, "J");
	int j = strtol(attr.c_str(), NULL, 10);
	attr = XMLReaderHelper::Attribute(reader, "K");
	int k = strtol(attr.c_str(), NULL, 10);
	attr = XMLReaderHelper::Attribute(reader, "Valid");
	bool beValid = true;
	if (!attr.empty()) {
		if (geo3dml::IsiEqual(attr, "false") || attr == "0") {
			beValid = false;
		}
	}
	grid->SetCellValidation(i, j, k, beValid);
	return true;
}
