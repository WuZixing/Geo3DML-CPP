// UTF-8编码
#include <g3dxml/XMLCuboidVolumeReader.h>
#include <geo3dml/Utils.h>

using namespace g3dxml;

const std::string XMLCuboidVolumeReader::Element = "GeoCuboidVolume";
const std::string XMLCuboidVolumeReader::Element_Vertex = "Vertex";
const std::string XMLCuboidVolumeReader::Element_Cuboid = "Cuboid";
const std::string XMLCuboidVolumeReader::Element_VertexList = "VertexList";

XMLCuboidVolumeReader::XMLCuboidVolumeReader(geo3dml::ObjectFactory* factory) {
    g3dFactory_ = factory;
}

XMLCuboidVolumeReader::~XMLCuboidVolumeReader() {

}

geo3dml::CuboidVolume* XMLCuboidVolumeReader::ReadCuboidVolume(xmlTextReaderPtr reader) {
	geo3dml::CuboidVolume* cuboidVolume = g3dFactory_->NewCuboidVolume();
	cuboidVolume->SetID(XMLReaderHelper::AttributeGMLID(reader));
	int status = xmlTextReaderRead(reader);
	while (status == 1) {
		const char* localName = (const char*)xmlTextReaderConstLocalName(reader);
		int nodeType = xmlTextReaderNodeType(reader);
		if (nodeType == XML_READER_TYPE_END_ELEMENT && geo3dml::IsiEqual(localName, Element)) {
			break;
		} else if (nodeType == XML_READER_TYPE_ELEMENT) {
			if (geo3dml::IsiEqual(localName, Element_Vertex)) {
				if (!ReadVertex(reader, cuboidVolume)) {
					break;
				}
			} else if (geo3dml::IsiEqual(localName, Element_Cuboid)) {
				if (!ReadCuboid(reader, cuboidVolume)) {
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
		delete cuboidVolume;
		cuboidVolume = nullptr;
	}
	return cuboidVolume;
}

bool XMLCuboidVolumeReader::ReadVertex(xmlTextReaderPtr reader, geo3dml::CuboidVolume* cuboidVolume) {
	// std::string index = XMLReaderHelper::Attribute(reader, "IndexNo");
	// long idx = strtol(index.c_str(), nullptr, 10);
	std::string coordinates;
	if (XMLReaderHelper::TextNode(reader, Element_Vertex, coordinates)) {
		char* end = nullptr;
		double x = strtod(coordinates.c_str(), &end);
		double y = strtod(end, &end);
		double z = strtod(end, nullptr);
		cuboidVolume->AppendVertex(x, y, z);
		return true;
	} else {
		SetStatus(false, coordinates);
		return false;
	}
}

bool XMLCuboidVolumeReader::ReadCuboid(xmlTextReaderPtr reader, geo3dml::CuboidVolume* cuboidVolume) {
	// std::string index = XMLReaderHelper::Attribute(reader, "IndexNo");
	// long idx = strtol(index.c_str(), NULL, 10);
	int status = xmlTextReaderRead(reader);
	while (status == 1) {
		const char* localName = (const char*)xmlTextReaderConstLocalName(reader);
		int nodeType = xmlTextReaderNodeType(reader);
		if (nodeType == XML_READER_TYPE_END_ELEMENT && geo3dml::IsiEqual(localName, Element_Cuboid)) {
			break;
		} else if (nodeType == XML_READER_TYPE_ELEMENT) {
			if (geo3dml::IsiEqual(localName, Element_VertexList)) {
				std::string ids;
				if (XMLReaderHelper::TextNode(reader, Element_VertexList, ids)) {
					char* end = nullptr;
					long v1 = strtol(ids.c_str(), &end, 10);
					long v2 = strtol(end, &end, 10);
					long v3 = strtol(end, &end, 10);
					long v4 = strtol(end, &end, 10);
					long v5 = strtol(end, &end, 10);
					long v6 = strtol(end, &end, 10);
					long v7 = strtol(end, &end, 10);
					long v8 = strtol(end, nullptr, 10);
					cuboidVolume->AppendCuboid(v1, v2, v3, v4, v5, v6, v7, v8);
				} else {
					SetStatus(false, ids);
					break;
				}
			}
		}
		status = xmlTextReaderRead(reader);
	}
	if (status != 1) {
		std::string err = XMLReaderHelper::FormatErrorMessageWithPosition(reader, "missing end element of " + Element_Cuboid);
		SetStatus(false, err);
	}
	return IsOK();
}
