// UTF-8编码
#include <g3dxml/XMLMultiLineStringReader.h>
#include <g3dxml/XMLLineStringReader.h>
#include <geo3dml/Utils.h>

using namespace g3dxml;

const std::string XMLMultiLineStringReader::Element("MultiCurve");

XMLMultiLineStringReader::XMLMultiLineStringReader(geo3dml::ObjectFactory* factory) {
    g3dFactory_ = factory;
}

XMLMultiLineStringReader::~XMLMultiLineStringReader() {

}

geo3dml::MultiLineString* XMLMultiLineStringReader::ReadMultiLineString(xmlTextReaderPtr reader) {
	geo3dml::MultiLineString* lines = g3dFactory_->NewMultiLineString();
	lines->SetID(XMLReaderHelper::AttributeGMLID(reader));
	int status = xmlTextReaderRead(reader);
	while (status == 1) {
		const char* localName = (const char*)xmlTextReaderConstLocalName(reader);
		int nodeType = xmlTextReaderNodeType(reader);
		if (nodeType == XML_READER_TYPE_END_ELEMENT && geo3dml::IsiEqual(localName, Element)) {
			break;
		} else if (nodeType == XML_READER_TYPE_ELEMENT) {
			if (geo3dml::IsiEqual(localName, XMLLineStringReader::Element)) {
				XMLLineStringReader lineReader(g3dFactory_);
				geo3dml::LineString* line = lineReader.ReadLineString(reader);
				if (line != nullptr) {
					lines->AddLineString(line);
					delete line;
					line = nullptr;
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
		delete lines;
		lines = nullptr;
	}
	return lines;
}
