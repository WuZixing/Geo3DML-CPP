#include <g3dxml/XMLPointReader.h>
#include <geo3dml/Utils.h>

using namespace g3dxml;

const std::string XMLPointReader::Element = "Point";

XMLPointReader::XMLPointReader(geo3dml::ObjectFactory* factory) {
	g3dFactory_ = factory;
}

XMLPointReader::~XMLPointReader() {

}

geo3dml::Point* XMLPointReader::ReadPoint(xmlTextReaderPtr reader) {
	geo3dml::Point* pt = g3dFactory_->NewPoint();
	pt->SetID(XMLReaderHelper::AttributeGMLID(reader));
	int status = xmlTextReaderRead(reader);
	while (status == 1) {
		const char* localName = (const char*)xmlTextReaderConstLocalName(reader);
		int nodeType = xmlTextReaderNodeType(reader);
		if (nodeType == XML_READER_TYPE_END_ELEMENT && geo3dml::IsiEqual(localName, Element)) {
			break;
		} else if (nodeType == XML_READER_TYPE_ELEMENT) {
			if (geo3dml::IsiEqual(localName, "pos")) {
				std::string strSrsDimension = XMLReaderHelper::Attribute(reader, "srsDimension");
				int srsDimension = atoi(strSrsDimension.c_str());
				std::string posList;
				if (!XMLReaderHelper::TextNode(reader, "pos", posList)) {
					SetStatus(false, posList);
					break;
				}
				char* end = NULL;
				double x = strtod(posList.c_str(), &end);
				double y = strtod(end, &end);
				double z = strtod(end, NULL);
				pt->SetPosition(x, y, z);
			}
		}
		status = xmlTextReaderRead(reader);
	}
	if (status != 1) {
		std::string err = XMLReaderHelper::FormatErrorMessageWithPosition(reader, "missing end element of " + Element);
		SetStatus(false, err);
	}
	if (!IsOK()) {
		delete pt;
		pt = NULL;
	}
	return pt;
}
