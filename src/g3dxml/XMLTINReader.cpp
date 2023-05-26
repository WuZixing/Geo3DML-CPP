#include <g3dxml/XMLTINReader.h>
#include <geo3dml/Utils.h>

using namespace g3dxml;

std::string XMLTINReader::Element = "GeoTin";
std::string XMLTINReader::Element_Vertex = "Vertex";
std::string XMLTINReader::Element_Triangle = "Triangle";
std::string XMLTINReader::Element_VertexList = "VertexList";
std::string XMLTINReader::Element_NeighborList = "NeighborList";

XMLTINReader::XMLTINReader(geo3dml::ObjectFactory* factory) {
	g3dFactory_ = factory;
}

XMLTINReader::~XMLTINReader() {

}

geo3dml::TIN* XMLTINReader::ReadTIN(xmlTextReaderPtr reader) {
	geo3dml::TIN* tin = g3dFactory_->NewTIN();
	tin->SetID(XMLReaderHelper::AttributeGMLID(reader));
	int status = xmlTextReaderRead(reader);
	while (status == 1) {
		const char* localName = (const char*)xmlTextReaderConstLocalName(reader);
		int nodeType = xmlTextReaderNodeType(reader);
		if (nodeType == XML_READER_TYPE_END_ELEMENT && geo3dml::IsiEqual(localName, Element)) {
			break;
		} else if (nodeType == XML_READER_TYPE_ELEMENT) {
			if (geo3dml::IsiEqual(localName, Element_Vertex)) {
				if (!ReadVertex(reader, tin)) {
					break;
				}
			} else if (geo3dml::IsiEqual(localName, Element_Triangle)) {
				if (!ReadTriangle(reader, tin)) {
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
		delete tin;
		tin = NULL;
	}
	return tin;
}

bool XMLTINReader::ReadVertex(xmlTextReaderPtr reader, geo3dml::TIN* tin) {
	// std::string index = XMLReaderHelper::Attribute(reader, "IndexNo");
	// long idx = strtol(index.c_str(), NULL, 10);
	std::string coordinates;
	if (XMLReaderHelper::TextNode(reader, Element_Vertex, coordinates)) {
		char* end = NULL;
		double x = strtod(coordinates.c_str(), &end);
		double y = strtod(end, &end);
		double z = strtod(end, NULL);
		tin->AppendVertex(x, y, z);
		return true;
	} else {
		SetStatus(false, coordinates);
		return false;
	}
}

bool XMLTINReader::ReadTriangle(xmlTextReaderPtr reader, geo3dml::TIN* tin) {
	// std::string index = XMLReaderHelper::Attribute(reader, "IndexNo");
	// long triangleIndex = strtol(index.c_str(), NULL, 10);
	int status = xmlTextReaderRead(reader);
	while (status == 1) {
		const char* localName = (const char*)xmlTextReaderConstLocalName(reader);
		int nodeType = xmlTextReaderNodeType(reader);
		if (nodeType == XML_READER_TYPE_END_ELEMENT && geo3dml::IsiEqual(localName, Element_Triangle)) {
			break;
		} else if (nodeType == XML_READER_TYPE_ELEMENT) {
			if (geo3dml::IsiEqual(localName, Element_VertexList)) {
				std::string ids;
				if (XMLReaderHelper::TextNode(reader, Element_VertexList, ids)) {
					char* end = NULL;
					long v1 = strtol(ids.c_str(), &end, 10);
					long v2 = strtol(end, &end, 10);
					long v3 = strtol(end, NULL, 10);
					tin->AppendTriangle(v1, v2, v3);
				} else {
					SetStatus(false, ids);
					break;
				}
			}
			// TODO: reader neighbours.
		}
		status = xmlTextReaderRead(reader);
	}
	if (status != 1) {
		std::string err = XMLReaderHelper::FormatErrorMessageWithPosition(reader, "missing end element of " + Element_Triangle);
		SetStatus(false, err);
	}
	return IsOK();
}