#include <g3dxml/XMLMapReader.h>
#include <g3dxml/XMLLayerReader.h>
#include <geo3dml/Utils.h>

using namespace g3dxml;

std::string XMLMapReader::Element = "Geo3DMap";
std::string XMLMapReader::Element_Name = "Name";
std::string XMLMapReader::Element_Description = "Description";

XMLMapReader::XMLMapReader(geo3dml::ObjectFactory* factory) {
	g3dFactory_ = factory;
}

XMLMapReader::~XMLMapReader() {
	g3dFactory_ = NULL;
}

geo3dml::Map* XMLMapReader::ReadMap(xmlTextReaderPtr reader) {
	geo3dml::Map* map = g3dFactory_->NewMap();
	std::string mapId = XMLReaderHelper::Attribute(reader, "ID");
	if (mapId.empty()) {
		mapId = geo3dml::Object::NewID();
	}
	map->SetID(mapId);
	int status = xmlTextReaderRead(reader);
	while (status == 1) {
		const char* localName = (const char*)xmlTextReaderConstLocalName(reader);
		int nodeType = xmlTextReaderNodeType(reader);
		/// TODO: parse metadata, feature relationship.
		if (nodeType == XML_READER_TYPE_END_ELEMENT && geo3dml::IsiEqual(localName, Element)) {
			break;
		} else if (nodeType == XML_READER_TYPE_ELEMENT) {
			if (geo3dml::IsiEqual(localName, Element_Name)) {
				std::string v;
				if (!XMLReaderHelper::TextNode(reader, Element_Name, v)) {
					SetStatus(false, v);
					break;
				}
				map->SetName(v);
			} else if (geo3dml::IsiEqual(localName, Element_Description)) {
				std::string v;
				if (!XMLReaderHelper::TextNode(reader, Element_Description, v)) {
					SetStatus(false, v);
					break;
				}
				map->SetDescription(v);
			} else if (geo3dml::IsiEqual(localName, XMLLayerReader::Element)) {
				XMLLayerReader layerReader(g3dFactory_);
				geo3dml::Layer* layer = layerReader.ReadLayer(reader);
				if (layer != NULL) {
					map->AddLayer(layer);
				} else if (!layerReader.IsOK()) {
					SetStatus(false, layerReader.Error());
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
		delete map;
		map = NULL;
	}
	return map;
}

geo3dml::Map* XMLMapReader::LoadFromFile(const std::string& file) {
	std::string fileEncoding = XMLReaderHelper::DectectFileEncoding(file);
	if (!XMLReaderHelper::IsUTF8(fileEncoding)) {
		SetStatus(false, "unsupported encoding " + fileEncoding + " of file " + file);
		return NULL;
	}
	geo3dml::Map* map = NULL;
	xmlTextReaderPtr reader = xmlReaderForFile(file.c_str(), fileEncoding.c_str(), 0);
	if (reader != NULL) {
		int status = xmlTextReaderRead(reader);
		while (status == 1) {
			const char* localName = (const char*)xmlTextReaderConstLocalName(reader);
			int nodeType = xmlTextReaderNodeType(reader);
			if (nodeType != XML_READER_TYPE_ELEMENT) {
				status = xmlTextReaderRead(reader);
				continue;
			}
			if (geo3dml::IsiEqual(localName, Element)) {
				map = ReadMap(reader);
				break;
			}
			status = xmlTextReaderRead(reader);
		}
		if (status != 1) {
			std::string err = XMLReaderHelper::FormatErrorMessageWithPosition(reader, "failed to parse file " + file);
			SetStatus(false, err);
		}
		xmlTextReaderClose(reader);
		xmlFreeTextReader(reader);
	} else {
		SetStatus(false, "failed to open file " + file);
	}
	return map;
}
