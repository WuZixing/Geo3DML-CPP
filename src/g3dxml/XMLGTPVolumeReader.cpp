// UTF-8编码
#include <g3dxml/XMLGTPVolumeReader.h>
#include <geo3dml/Utils.h>

using namespace g3dxml;

const std::string XMLGTPVolumeReader::Element = "GTPVolume";
const std::string XMLGTPVolumeReader::Element_Vertex = "Vertex";
const std::string XMLGTPVolumeReader::Element_Prism = "Prism";
const std::string XMLGTPVolumeReader::Element_TopTriangle = "TopTriangle";
const std::string XMLGTPVolumeReader::Element_BottomTriangle = "BottomTriangle";
const std::string XMLGTPVolumeReader::Element_NeighborList = "NeighborList";


XMLGTPVolumeReader::XMLGTPVolumeReader(geo3dml::ObjectFactory* factory) {
    g3dFactory_ = factory;
}

XMLGTPVolumeReader::~XMLGTPVolumeReader() {

}

geo3dml::GTPVolume* XMLGTPVolumeReader::ReadVolume(xmlTextReaderPtr reader) {
    geo3dml::GTPVolume* gtp = g3dFactory_->NewGTPVolume();
    gtp->SetID(XMLReaderHelper::AttributeGMLID(reader));
	int status = xmlTextReaderRead(reader);
	while (status == 1) {
		const char* localName = (const char*)xmlTextReaderConstLocalName(reader);
		int nodeType = xmlTextReaderNodeType(reader);
		if (nodeType == XML_READER_TYPE_END_ELEMENT && geo3dml::IsiEqual(localName, Element)) {
			break;
		} else if (nodeType == XML_READER_TYPE_ELEMENT) {
			if (geo3dml::IsiEqual(localName, Element_Vertex)) {
				if (!ReadVertex(reader, gtp)) {
					break;
				}
			} else if (geo3dml::IsiEqual(localName, Element_Prism)) {
				if (!ReadPrism(reader, gtp)) {
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
		delete gtp;
		gtp = nullptr;
	}
    return gtp;
}

bool XMLGTPVolumeReader::ReadVertex(xmlTextReaderPtr reader, geo3dml::GTPVolume* gtp) {
	std::string index = XMLReaderHelper::Attribute(reader, "IndexNo");
	long idx = strtol(index.c_str(), nullptr, 10);
	std::string coordinates;
	if (XMLReaderHelper::TextNode(reader, Element_Vertex, coordinates)) {
		char* end = nullptr;
		double x = strtod(coordinates.c_str(), &end);
		double y = strtod(end, &end);
		double z = strtod(end, nullptr);
		gtp->AppendVertex(x, y, z);
		return true;
	} else {
		SetStatus(false, coordinates);
		return false;
	}
}

bool XMLGTPVolumeReader::ReadPrism(xmlTextReaderPtr reader, geo3dml::GTPVolume* gtp) {
	std::string index = XMLReaderHelper::Attribute(reader, "IndexNo");
	long prismIndex = strtol(index.c_str(), nullptr, 10);
	int status = xmlTextReaderRead(reader);
	int topVertex1 = -1, topVertex2 = -1, topVertex3 = -1;
	int bottomVertex1 = -1, bottomVertex2 = -1, bottomVertex3 = -1;
	int neighbor1 = -1, neighbor2 = -1, neighbor3 = -1;
	while (status == 1) {
		const char* localName = (const char*)xmlTextReaderConstLocalName(reader);
		int nodeType = xmlTextReaderNodeType(reader);
		if (nodeType == XML_READER_TYPE_END_ELEMENT && geo3dml::IsiEqual(localName, Element_Prism)) {
			break;
		} else if (nodeType == XML_READER_TYPE_ELEMENT) {
			if (geo3dml::IsiEqual(localName, Element_TopTriangle)) {
				std::string ids;
				if (XMLReaderHelper::TextNode(reader, Element_TopTriangle, ids)) {
					char* end = nullptr;
					topVertex1 = strtol(ids.c_str(), &end, 10);
					topVertex2 = strtol(end, &end, 10);
					topVertex3 = strtol(end, nullptr, 10);
				} else {
					SetStatus(false, ids);
					break;
				}
			} else if (geo3dml::IsiEqual(localName, Element_BottomTriangle)) {
				std::string ids;
				if (XMLReaderHelper::TextNode(reader, Element_BottomTriangle, ids)) {
					char* end = nullptr;
					bottomVertex1 = strtol(ids.c_str(), &end, 10);
					bottomVertex2 = strtol(end, &end, 10);
					bottomVertex3 = strtol(end, nullptr, 10);
				} else {
					SetStatus(false, ids);
					break;
				}
			} else if (geo3dml::IsiEqual(localName, Element_NeighborList)) {
				std::string ids;
				if (XMLReaderHelper::TextNode(reader, Element_NeighborList, ids)) {
					char* end = nullptr;
					neighbor1 = strtol(ids.c_str(), &end, 10);
					neighbor2 = strtol(end, &end, 10);
					neighbor3 = strtol(end, nullptr, 10);
				} else {
					SetStatus(false, ids);
					break;
				}
			}
		}
		status = xmlTextReaderRead(reader);
	}
	if (status != 1) {
		std::string err = XMLReaderHelper::FormatErrorMessageWithPosition(reader, "missing end element of " + Element_Prism);
		SetStatus(false, err);
	} else {
		if (topVertex1 >= 0 && topVertex2 >= 0 && topVertex3 >= 0 && bottomVertex1 >= 0 && bottomVertex2 >= 0 && bottomVertex3 >= 0) {
			gtp->AppendPrism(topVertex1, topVertex2, topVertex3, bottomVertex1, bottomVertex2, bottomVertex3);
		} else {
			std::string err = XMLReaderHelper::FormatErrorMessageWithPosition(reader, "missing element of TopTriangle or BottomTriangle for element Prism");
			SetStatus(false, err);
		}
	}
	return IsOK();
}
