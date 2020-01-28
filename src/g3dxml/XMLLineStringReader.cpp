#include <g3dxml/XMLLineStringReader.h>
#include <geo3dml/Utils.h>

using namespace g3dxml;

std::string XMLLineStringReader::Element = "LineString";

XMLLineStringReader::XMLLineStringReader(geo3dml::ObjectFactory* factory) {
	g3dFactory_ = factory;
}

XMLLineStringReader::~XMLLineStringReader() {
	
}

geo3dml::LineString* XMLLineStringReader::ReadLineString(xmlTextReaderPtr reader) {
	geo3dml::LineString* line = g3dFactory_->NewLineString();
	line->SetID(XMLReaderHelper::AttributeGMLID(reader));
	int status = xmlTextReaderRead(reader);
	while (status == 1) {
		const char* localName = (const char*)xmlTextReaderConstLocalName(reader);
		int nodeType = xmlTextReaderNodeType(reader);
		if (nodeType == XML_READER_TYPE_END_ELEMENT && geo3dml::IsiEqual(localName, Element)) {
			break;
		} else if (nodeType == XML_READER_TYPE_ELEMENT) {
			if (geo3dml::IsiEqual(localName, "posList")) {
				std::string strSrsDimension = XMLReaderHelper::Attribute(reader, "srsDimension");
				std::string strCount = XMLReaderHelper::Attribute(reader, "count");
				int srsDimension = atoi(strSrsDimension.c_str());
				int count = atoi(strCount.c_str());
				std::string posList;
				if (!XMLReaderHelper::TextNode(reader, "posList", posList)) {
					SetStatus(false, posList);
					break;
				}
				int posCount = srsDimension * count;
				if (posCount >= 3) {
					char* end = NULL;
					double x = strtod(posList.c_str(), &end);
					double y = strtod(end, &end);
					double z = strtod(end, &end);
					line->AddVertex(x, y, z);
					posCount -= 3;
					while (posCount > 0) {
						x = strtod(end, &end);
						y = strtod(end, &end);
						z = strtod(end, &end);
						line->AddVertex(x, y, z);
						posCount -= 3;
					}
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
		delete line;
		line = NULL;
	}
	return line;
}
