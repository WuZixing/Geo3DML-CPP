// UTF-8编码
#include <g3dxml/XMLTetrahedronVolumeReader.h>
#include <geo3dml/Utils.h>

using namespace g3dxml;

const std::string XMLTetrahedronVolumeReader::Element = "GeoTetrahedronVolume";
const std::string XMLTetrahedronVolumeReader::Element_Vertex = "Vertex";
const std::string XMLTetrahedronVolumeReader::Element_Tetrahedron = "Tetrahedron";
const std::string XMLTetrahedronVolumeReader::Element_VertexList = "VertexList";

XMLTetrahedronVolumeReader::XMLTetrahedronVolumeReader(geo3dml::ObjectFactory* factory) {
    g3dFactory_ = factory;
}

XMLTetrahedronVolumeReader::~XMLTetrahedronVolumeReader() {

}

geo3dml::TetrahedronVolume* XMLTetrahedronVolumeReader::ReadTetrahedronVolume(xmlTextReaderPtr reader) {
	geo3dml::TetrahedronVolume* tetraVolume = g3dFactory_->NewTetrahedronVolume();
	tetraVolume->SetID(XMLReaderHelper::AttributeGMLID(reader));
	int status = xmlTextReaderRead(reader);
	while (status == 1) {
		const char* localName = (const char*)xmlTextReaderConstLocalName(reader);
		int nodeType = xmlTextReaderNodeType(reader);
		if (nodeType == XML_READER_TYPE_END_ELEMENT && geo3dml::IsiEqual(localName, Element)) {
			break;
		} else if (nodeType == XML_READER_TYPE_ELEMENT) {
			if (geo3dml::IsiEqual(localName, Element_Vertex)) {
				if (!ReadVertex(reader, tetraVolume)) {
					break;
				}
			} else if (geo3dml::IsiEqual(localName, Element_Tetrahedron)) {
				if (!ReadTetrahedron(reader, tetraVolume)) {
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
		delete tetraVolume;
		tetraVolume = nullptr;
	}
	return tetraVolume;
}

bool XMLTetrahedronVolumeReader::ReadVertex(xmlTextReaderPtr reader, geo3dml::TetrahedronVolume* tetraVolume) {
	// std::string index = XMLReaderHelper::Attribute(reader, "IndexNo");
	// long idx = strtol(index.c_str(), nullptr, 10);
	std::string coordinates;
	if (XMLReaderHelper::TextNode(reader, Element_Vertex, coordinates)) {
		char* end = nullptr;
		double x = strtod(coordinates.c_str(), &end);
		double y = strtod(end, &end);
		double z = strtod(end, nullptr);
		tetraVolume->AppendVertex(x, y, z);
		return true;
	} else {
		SetStatus(false, coordinates);
		return false;
	}
}

bool XMLTetrahedronVolumeReader::ReadTetrahedron(xmlTextReaderPtr reader, geo3dml::TetrahedronVolume* tetraVolume) {
	// std::string index = XMLReaderHelper::Attribute(reader, "IndexNo");
	// long idx = strtol(index.c_str(), NULL, 10);
	int status = xmlTextReaderRead(reader);
	while (status == 1) {
		const char* localName = (const char*)xmlTextReaderConstLocalName(reader);
		int nodeType = xmlTextReaderNodeType(reader);
		if (nodeType == XML_READER_TYPE_END_ELEMENT && geo3dml::IsiEqual(localName, Element_Tetrahedron)) {
			break;
		} else if (nodeType == XML_READER_TYPE_ELEMENT) {
			if (geo3dml::IsiEqual(localName, Element_VertexList)) {
				std::string ids;
				if (XMLReaderHelper::TextNode(reader, Element_VertexList, ids)) {
					char* end = nullptr;
					long v1 = strtol(ids.c_str(), &end, 10);
					long v2 = strtol(end, &end, 10);
					long v3 = strtol(end, &end, 10);
					long v4 = strtol(end, nullptr, 10);
					tetraVolume->AppendTetrahedron(v1, v2, v3, v4);
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
		std::string err = XMLReaderHelper::FormatErrorMessageWithPosition(reader, "missing end element of " + Element_Tetrahedron);
		SetStatus(false, err);
	}
	return IsOK();
}
