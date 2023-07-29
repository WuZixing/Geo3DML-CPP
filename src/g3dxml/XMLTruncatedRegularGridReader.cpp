// UTF-8编码
#include <g3dxml/XMLTruncatedRegularGridReader.h>
#include <geo3dml/Utils.h>

using namespace g3dxml;

const std::string XMLTruncatedRegularGridReader::Element = "GeoTruncatedRegularGrid";
const std::string XMLTruncatedRegularGridReader::Element_PlaneGrid = "PlaneGrid";
const std::string XMLTruncatedRegularGridReader::Element_Vertex = "Vertex";
const std::string XMLTruncatedRegularGridReader::Element_Face = "Face";
const std::string XMLTruncatedRegularGridReader::Element_Cell = "Cell";

XMLTruncatedRegularGridReader::XMLTruncatedRegularGridReader(geo3dml::ObjectFactory* factory) {
	g3dFactory_ = factory;
}

XMLTruncatedRegularGridReader::~XMLTruncatedRegularGridReader() {

}

geo3dml::TruncatedRegularGrid* XMLTruncatedRegularGridReader::ReadGrid(xmlTextReaderPtr reader) {
	geo3dml::TruncatedRegularGrid* trGrid = g3dFactory_->NewTruncatedRegularGrid();
	trGrid->SetID(XMLReaderHelper::AttributeGMLID(reader));
	int status = xmlTextReaderRead(reader);
	while (status == 1) {
		const char* localName = (const char*)xmlTextReaderConstLocalName(reader);
		int nodeType = xmlTextReaderNodeType(reader);
		if (nodeType == XML_READER_TYPE_END_ELEMENT && geo3dml::IsiEqual(localName, Element)) {
			break;
		} else if (nodeType == XML_READER_TYPE_ELEMENT) {
			if (geo3dml::IsiEqual(localName, Element_PlaneGrid)) {
				if (!ReadPlaneGrid(reader, trGrid)) {
					break;
				}
			} else if (geo3dml::IsiEqual(localName, Element_Vertex)) {
				if (!ReadVertex(reader, trGrid)) {
					break;
				}
			} else if (geo3dml::IsiEqual(localName, Element_Face)) {
				if (!ReadFace(reader, trGrid)) {
					break;
				}
			} else if (geo3dml::IsiEqual(localName, Element_Cell)) {
				if (!ReadCell(reader, trGrid)) {
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
		delete trGrid;
		trGrid = nullptr;
	}
	return trGrid;
}

bool XMLTruncatedRegularGridReader::ReadPlaneGrid(xmlTextReaderPtr reader, geo3dml::TruncatedRegularGrid* trGrid) {
	std::string v;
	int status = xmlTextReaderRead(reader);
	while (status == 1) {
		const char* localName = (const char*)xmlTextReaderConstLocalName(reader);
		int nodeType = xmlTextReaderNodeType(reader);
		if (nodeType == XML_READER_TYPE_END_ELEMENT && geo3dml::IsiEqual(localName, Element_PlaneGrid)) {
			break;
		} else if (geo3dml::IsiEqual(localName, "Origin")) {
			v = XMLReaderHelper::Attribute(reader, "gml:srsDimension");
			if (v.empty()) {
				v = XMLReaderHelper::Attribute(reader, "srsDimension");
			}
			long dim = strtol(v.c_str(), nullptr, 10);
			if (XMLReaderHelper::TextNode(reader, "Origin", v)) {
				geo3dml::Point3D pt3D;
				char* end = nullptr;
				pt3D.x = strtod(v.c_str(), &end);
				pt3D.y = strtod(end, &end);
				if (dim > 2) {
					pt3D.z = strtod(end, nullptr);
				}
				trGrid->SetPlaneGridOrigin(pt3D);
			} else {
				SetStatus(false, v);
				break;
			}
		} else if (geo3dml::IsiEqual(localName, "Azimuth")) {
			if (XMLReaderHelper::TextNode(reader, "Azimuth", v)) {
				trGrid->SetPlaneGridAzimuth(strtod(v.c_str(), nullptr));
			} else {
				SetStatus(false, v);
				break;
			}
		} else if (geo3dml::IsiEqual(localName, "Steps")) {
			if (XMLReaderHelper::TextNode(reader, "Steps", v)) {
				char* end = nullptr;
				double stepX = strtod(v.c_str(), &end);
				double stepY = strtod(end, nullptr);
				trGrid->SetPlaneGridCellSize(stepX, stepY);
			} else {
				SetStatus(false, v);
				break;
			}
		} else if (geo3dml::IsiEqual(localName, "Dimension")) {
			if (XMLReaderHelper::TextNode(reader, "Dimension", v)) {
				char* end = nullptr;
				long dimX = strtol(v.c_str(), &end, 10);
				long dimY = strtol(end, nullptr, 10);
				trGrid->SetPlaneGridCellNumber(dimX, dimY);
			} else {
				SetStatus(false, v);
				break;
			}
		}
		status = xmlTextReaderRead(reader);
	}
	if (status != 1) {
		std::string err = XMLReaderHelper::FormatErrorMessageWithPosition(reader, "missing end element of " + Element_PlaneGrid);
		SetStatus(false, err);
	}
	return IsOK();
}

bool XMLTruncatedRegularGridReader::ReadVertex(xmlTextReaderPtr reader, geo3dml::TruncatedRegularGrid* trGrid) {
	// std::string index = XMLReaderHelper::Attribute(reader, "IndexNo");
	// long idx = strtol(index.c_str(), nullptr, 10);
	std::string coordinates;
	if (XMLReaderHelper::TextNode(reader, Element_Vertex, coordinates)) {
		char* end = nullptr;
		double x = strtod(coordinates.c_str(), &end);
		double y = strtod(end, &end);
		double z = strtod(end, nullptr);
		trGrid->AppendVertex(x, y, z);
		return true;
	} else {
		SetStatus(false, coordinates);
		return false;
	}
}

bool XMLTruncatedRegularGridReader::ReadFace(xmlTextReaderPtr reader, geo3dml::TruncatedRegularGrid* trGrid) {
	// std::string index = XMLReaderHelper::Attribute(reader, "IndexNo");
	// long idx = strtol(index.c_str(), NULL, 10);
	int status = xmlTextReaderRead(reader);
	while (status == 1) {
		const char* localName = (const char*)xmlTextReaderConstLocalName(reader);
		int nodeType = xmlTextReaderNodeType(reader);
		if (nodeType == XML_READER_TYPE_END_ELEMENT && geo3dml::IsiEqual(localName, Element_Face)) {
			break;
		} else if (nodeType == XML_READER_TYPE_ELEMENT) {
			if (geo3dml::IsiEqual(localName, "VertexList")) {
				std::string strLen = XMLReaderHelper::Attribute(reader, "Length");
				long len = strtol(strLen.c_str(), nullptr, 10);
				std::string ids;
				if (XMLReaderHelper::TextNode(reader, "VertexList", ids)) {
					std::list<int> pts;
					char* end = nullptr;
					long idx = strtol(ids.c_str(), &end, 10);
					pts.push_back(idx);
					while (--len > 0) {
						idx = strtol(end, &end, 10);
						pts.push_back(idx);
					}
					if (len < 1) {
						trGrid->AppendFace(pts);
					} else {
						std::string err = XMLReaderHelper::FormatErrorMessageWithPosition(reader, "invalid vertex list for a face");
						SetStatus(false, err);
						break;
					}
				} else {
					SetStatus(false, ids);
					break;
				}
			}
		}
		status = xmlTextReaderRead(reader);
	}
	if (status != 1) {
		std::string err = XMLReaderHelper::FormatErrorMessageWithPosition(reader, "missing end element of " + Element_Face);
		SetStatus(false, err);
	}
	return IsOK();
}

bool XMLTruncatedRegularGridReader::ReadCell(xmlTextReaderPtr reader, geo3dml::TruncatedRegularGrid* trGrid) {
	// std::string index = XMLReaderHelper::Attribute(reader, "IndexNo");
	// long idx = strtol(index.c_str(), NULL, 10);
	std::string v = XMLReaderHelper::Attribute(reader, "I");
	int i = strtol(v.c_str(), nullptr, 10);
	v = XMLReaderHelper::Attribute(reader, "J");
	int j = strtol(v.c_str(), nullptr, 10);
	v = XMLReaderHelper::Attribute(reader, "K");
	int k = strtol(v.c_str(), nullptr, 10);
	int status = xmlTextReaderRead(reader);
	while (status == 1) {
		const char* localName = (const char*)xmlTextReaderConstLocalName(reader);
		int nodeType = xmlTextReaderNodeType(reader);
		if (nodeType == XML_READER_TYPE_END_ELEMENT && geo3dml::IsiEqual(localName, Element_Cell)) {
			break;
		} else if (nodeType == XML_READER_TYPE_ELEMENT) {
			if (geo3dml::IsiEqual(localName, "FaceList")) {
				std::string strLen = XMLReaderHelper::Attribute(reader, "Length");
				long len = strtol(strLen.c_str(), nullptr, 10);
				if (XMLReaderHelper::TextNode(reader, "FaceList", v)) {
					std::list<int> faces;
					char* end = nullptr;
					long idx = strtol(v.c_str(), &end, 10);
					faces.push_back(idx);
					while (--len > 0) {
						idx = strtol(end, &end, 10);
						faces.push_back(idx);
					}
					if (len < 1) {
						trGrid->AppendCell(faces, i, j, k);
					} else {
						std::string err = XMLReaderHelper::FormatErrorMessageWithPosition(reader, "invalid face list for a cell");
						SetStatus(false, err);
						break;
					}
				} else {
					SetStatus(false, v);
					break;
				}
			}
		}
		status = xmlTextReaderRead(reader);
	}
	if (status != 1) {
		std::string err = XMLReaderHelper::FormatErrorMessageWithPosition(reader, "missing end element of " + Element_Cell);
		SetStatus(false, err);
	}
	return IsOK();
}

