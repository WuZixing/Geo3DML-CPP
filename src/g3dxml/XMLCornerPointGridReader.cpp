#include <g3dxml/XMLCornerPointGridReader.h>
#include <geo3dml/Utils.h>
#include <cmath>

using namespace g3dxml;

const std::string XMLCornerPointGridReader::Element = "GeoCornerPointGrid";
const std::string XMLCornerPointGridReader::Element_Dimension = "Dimension";
const std::string XMLCornerPointGridReader::Element_Pillar = "Pillar";
const std::string XMLCornerPointGridReader::Element_Pillar_HeadPos = "HeadPos";
const std::string XMLCornerPointGridReader::Element_Pillar_TailPos = "TailPos";
const std::string XMLCornerPointGridReader::Element_Cells = "Cells";
const std::string XMLCornerPointGridReader::Element_Cell = "Cell";

XMLCornerPointGridReader::XMLCornerPointGridReader(geo3dml::ObjectFactory* factory) {
	g3dFactory_ = factory;
}

XMLCornerPointGridReader::~XMLCornerPointGridReader() {
}

geo3dml::CornerPointGrid* XMLCornerPointGridReader::ReadCornerPointGrid(xmlTextReaderPtr reader) {
	geo3dml::CornerPointGrid* grid = NULL;
	std::string id = XMLReaderHelper::AttributeGMLID(reader);
	int status = xmlTextReaderRead(reader);
	while (status == 1) {
		const char* localName = (const char*)xmlTextReaderConstLocalName(reader);
		int nodeType = xmlTextReaderNodeType(reader);
		if (nodeType == XML_READER_TYPE_END_ELEMENT && geo3dml::IsiEqual(localName, Element)) {
			break;
		} else if (nodeType == XML_READER_TYPE_ELEMENT) {
			if (geo3dml::IsiEqual(localName, Element_Dimension)) {
				std::string dims;
				if (XMLReaderHelper::TextNode(reader, Element_Dimension, dims)) {
					if (grid == NULL) {
						char* end = NULL;
						long dimI = strtol(dims.c_str(), &end, 10);
						long dimJ = strtol(end, &end, 10);
						long dimK = strtol(end, NULL, 10);
						grid = g3dFactory_->NewCornerPointGrid(dimI, dimJ, dimK);
						grid->SetID(id);
					}
				} else {
					SetStatus(false, dims);
					break;
				}
			} else if (geo3dml::IsiEqual(localName, Element_Pillar)) {
				if (!ReadPillar(reader, grid)) {
					break;
				}
			} else if (geo3dml::IsiEqual(localName, Element_Cells)) {
				if (!ReadCells(reader, grid)) {
					break;
				}
			}
		}
		status = status = xmlTextReaderRead(reader);
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

bool XMLCornerPointGridReader::ReadPillar(xmlTextReaderPtr reader, geo3dml::CornerPointGrid* grid) {
	if (grid == NULL) {
		std::string err = XMLReaderHelper::FormatErrorMessageWithPosition(reader, "invalid geo3dml::CornerPointGrid object for reading pillar");
		SetStatus(false, err);
		return false;
	}
	bool hPosReady = false, tPosReady = false;
	double headPos[3], tailPos[3];
	int status = xmlTextReaderRead(reader);
	while (status == 1) {
		const char* localName = (const char*)xmlTextReaderConstLocalName(reader);
		int nodeType = xmlTextReaderNodeType(reader);
		if (nodeType == XML_READER_TYPE_END_ELEMENT && geo3dml::IsiEqual(localName, Element_Pillar)) {
			break;
		} else if (nodeType == XML_READER_TYPE_ELEMENT) {
			if (geo3dml::IsiEqual(localName, Element_Pillar_HeadPos)) {
				std::string coordinates;
				if (XMLReaderHelper::TextNode(reader, Element_Pillar_HeadPos, coordinates)) {
					char* end = NULL;
					headPos[0] = strtod(coordinates.c_str(), &end);
					headPos[1] = strtod(end, &end);
					headPos[2] = strtod(end, NULL);
					hPosReady = true;
				} else {
					SetStatus(false, coordinates);
					break;
				}
			} else if (geo3dml::IsiEqual(localName, Element_Pillar_TailPos)) {
				std::string coordinates;
				if (XMLReaderHelper::TextNode(reader, Element_Pillar_TailPos, coordinates)) {
					char* end = NULL;
					tailPos[0] = strtod(coordinates.c_str(), &end);
					tailPos[1] = strtod(end, &end);
					tailPos[2] = strtod(end, NULL);
					tPosReady = true;
				} else {
					SetStatus(false, coordinates);
					break;
				}
			}
		}
		status = xmlTextReaderRead(reader);
	}
	if (hPosReady && tPosReady) {
		grid->AddNextPillar(headPos, tailPos);
		return true;
	} else {
		if (status != 1) {
			std::string err = XMLReaderHelper::FormatErrorMessageWithPosition(reader, "missing end element of " + Element_Pillar);
			SetStatus(false, err);
		}
		return false;
	}
}

bool XMLCornerPointGridReader::ReadCells(xmlTextReaderPtr reader, geo3dml::CornerPointGrid* grid) {
	if (grid == NULL) {
		std::string err = XMLReaderHelper::FormatErrorMessageWithPosition(reader, "invalid geo3dml::CornerPointGrid object for reading cells");
		SetStatus(false, err);
		return false;
	}
	int dimI = 0, dimJ = 0, dimK = 0;
	grid->GetDimensions(dimI, dimJ, dimK);
	std::string attrZValue = XMLReaderHelper::Attribute(reader, "ZValue");
	int i = 0, j = 0, k = 0;
	int status = xmlTextReaderRead(reader);
	while (status == 1) {
		const char* localName = (const char*)xmlTextReaderConstLocalName(reader);
		int nodeType = xmlTextReaderNodeType(reader);
		if (nodeType == XML_READER_TYPE_END_ELEMENT && geo3dml::IsiEqual(localName, Element_Cells)) {
			break;
		} else if (nodeType == XML_READER_TYPE_ELEMENT) {
			if (geo3dml::IsiEqual(localName, Element_Cell)) {
				// read the cell: (i, j, k).
				if (!ReadCell(reader, grid, i, j, k, attrZValue)) {
					break;
				}
				++i;
				if (i >= dimI) {
					++j;
					i = 0;
				}
				if (j >= dimJ) {
					++k;
					j = 0;
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

bool XMLCornerPointGridReader::ReadCell(xmlTextReaderPtr reader, geo3dml::CornerPointGrid* grid, int i, int j, int k, const std::string& zValueTag) {
	std::string attrValid = XMLReaderHelper::Attribute(reader, "Valid");
	if (attrValid.empty()) {
		// Try to find the deprecated attribute "cellv".
		attrValid = XMLReaderHelper::Attribute(reader, "cellv");
	}
	bool beValid = strtol(attrValid.c_str(), NULL, 10) != 0;

	// z values from XML data.
	std::string coordinates;
	if (!XMLReaderHelper::TextNode(reader, Element_Cell, coordinates)) {
		SetStatus(false, coordinates);
		return false;
	}
	char* end = NULL;
	double bottomFrontLeftZ = strtod(coordinates.c_str(), &end);
	double bottomFrontRightZ = strtod(end, &end);
	double bottomBackLeftZ = strtod(end, &end);
	double bottomBackRightZ = strtod(end, &end);
	double topFrontLeftZ = strtod(end, &end);
	double topFrontRightZ = strtod(end, &end);
	double topBackLeftZ = strtod(end, &end);
	double topBackRightZ = strtod(end, NULL);

	// four pillars around the cell.
	double headOfBottomLeftPillar[3], tailOfBottomLeftPillar[3];
	grid->GetPillarAt(i, j, headOfBottomLeftPillar, tailOfBottomLeftPillar);
	double headOfBottomRightPillar[3], tailOfBottomRightPillar[3];
	grid->GetPillarAt(i + 1, j, headOfBottomRightPillar, tailOfBottomRightPillar);
	double headOfTopLeftPillar[3], tailOfTopLeftPillar[3];
	grid->GetPillarAt(i, j + 1, headOfTopLeftPillar, tailOfTopLeftPillar);
	double headOfTopRightPillar[3], tailOfTopRightPillar[3];
	grid->GetPillarAt(i + 1, j + 1, headOfTopRightPillar, tailOfTopRightPillar);

	// compute coordinates.
	double bottomFrontLeftPos[3], bottomFrontRightPos[3], bottomBackLeftPos[3], bottomBackRightPos[3];
	double topFrontLeftPos[3], topFrontRightPos[3], topBackLeftPos[3], topBackRightPos[3];
	if (geo3dml::IsiEqual(zValueTag, "elevation")) {
		ComputeZByElevation(headOfBottomLeftPillar, tailOfBottomLeftPillar, bottomFrontLeftZ, bottomFrontLeftPos);
		ComputeZByElevation(headOfBottomLeftPillar, tailOfBottomLeftPillar, topFrontLeftZ, topFrontLeftPos);
		ComputeZByElevation(headOfBottomRightPillar, tailOfBottomRightPillar, bottomFrontRightZ, bottomFrontRightPos);
		ComputeZByElevation(headOfBottomRightPillar, tailOfBottomRightPillar, topFrontRightZ, topFrontRightPos);
		ComputeZByElevation(headOfTopLeftPillar, tailOfTopLeftPillar, bottomBackLeftZ, bottomBackLeftPos);
		ComputeZByElevation(headOfTopLeftPillar, tailOfTopLeftPillar, topBackLeftZ, topBackLeftPos);
		ComputeZByElevation(headOfTopRightPillar, tailOfTopRightPillar, bottomBackRightZ, bottomBackRightPos);
		ComputeZByElevation(headOfTopRightPillar, tailOfTopRightPillar, topBackRightZ, topBackRightPos);
	} else if (geo3dml::IsiEqual(zValueTag, "length")) {
		ComputeZByLength(headOfBottomLeftPillar, tailOfBottomLeftPillar, bottomFrontLeftZ, bottomFrontLeftPos);
		ComputeZByLength(headOfBottomLeftPillar, tailOfBottomLeftPillar, topFrontLeftZ, topFrontLeftPos);
		ComputeZByLength(headOfBottomRightPillar, tailOfBottomRightPillar, bottomFrontRightZ, bottomFrontRightPos);
		ComputeZByLength(headOfBottomRightPillar, tailOfBottomRightPillar, topFrontRightZ, topFrontRightPos);
		ComputeZByLength(headOfTopLeftPillar, tailOfTopLeftPillar, bottomBackLeftZ, bottomBackLeftPos);
		ComputeZByLength(headOfTopLeftPillar, tailOfTopLeftPillar, topBackLeftZ, topBackLeftPos);
		ComputeZByLength(headOfTopRightPillar, tailOfTopRightPillar, bottomBackRightZ, bottomBackRightPos);
		ComputeZByLength(headOfTopRightPillar, tailOfTopRightPillar, topBackRightZ, topBackRightPos);
	}

	grid->AddNextCell(i, j, k, bottomFrontLeftPos, bottomFrontRightPos, bottomBackLeftPos, bottomBackRightPos, topFrontLeftPos, topFrontRightPos, topBackLeftPos, topBackRightPos, beValid);
	return true;
}

void XMLCornerPointGridReader::ComputeZByElevation(const double headPosOfPillar[3], const double tailPosOfPillar[3], const double& z, double pos[3]) {
	// t = (pt.z - pt0.z) / (pt1.z - pt0.z);
	// pt.x = pt0.x + t * (pt1.x - pt0.x)
	// pt.y = pt0.y + t * (pt1.y - pt0.y)
	pos[2] = z;
	double t = 0;
	double deltaZ = tailPosOfPillar[2] - headPosOfPillar[2];
	if (!geo3dml::IsZero(deltaZ)) {
		t = (pos[2] - headPosOfPillar[2]) / deltaZ;
	}	
	pos[0] = headPosOfPillar[0] + t * (tailPosOfPillar[0] - headPosOfPillar[0]);
	pos[1] = headPosOfPillar[1] + t * (tailPosOfPillar[1] - headPosOfPillar[1]);
}

void XMLCornerPointGridReader::ComputeZByLength(const double headPosOfPillar[3], const double tailPosOfPillar[3], const double& len, double pos[3]) {
	// t = len / (pt1.z - pt0.z);
	// pt.x = pt0.x + t * (pt1.x - pt0.x)
	// pt.y = pt0.y + t * (pt1.y - pt0.y)
	// pt.z = pt0.z + t * (pt1.z - pt0.z)
	double t = 0;
	double length = pow(tailPosOfPillar[0] - headPosOfPillar[0], 2) + pow(tailPosOfPillar[1] - headPosOfPillar[1], 2) + pow(tailPosOfPillar[2] - headPosOfPillar[2], 2);
	length = pow(length, 0.5);
	if (!geo3dml::IsZero(length)) {
		t = len / length;
	}
	pos[0] = headPosOfPillar[0] + t * (tailPosOfPillar[0] - headPosOfPillar[0]);
	pos[1] = headPosOfPillar[1] + t * (tailPosOfPillar[1] - headPosOfPillar[1]);
	pos[2] = headPosOfPillar[2] + t * (tailPosOfPillar[2] - headPosOfPillar[2]);
}
