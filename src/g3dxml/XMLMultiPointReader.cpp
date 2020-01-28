#include <g3dxml/XMLMultiPointReader.h>
#include <geo3dml/Utils.h>

using namespace g3dxml;

std::string XMLMultiPointReader::Element = "MultiPoint";

XMLMultiPointReader::XMLMultiPointReader(geo3dml::ObjectFactory* factory) {
	g3dFactory_ = factory;
}

XMLMultiPointReader::~XMLMultiPointReader() {

}

geo3dml::MultiPoint* XMLMultiPointReader::ReadMultiPoint(xmlTextReaderPtr reader) {
	geo3dml::MultiPoint* pts = g3dFactory_->NewMultiPoint();
	pts->SetID(XMLReaderHelper::AttributeGMLID(reader));
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
				pts->AddPoint(x, y, z);
			}
		}
		status = xmlTextReaderRead(reader);
	}
	if (status != 1) {
		std::string err = XMLReaderHelper::FormatErrorMessageWithPosition(reader, "missing end element of " + Element);
		SetStatus(false, err);
	}
	if (!IsOK()) {
		delete pts;
		pts = NULL;
	}
	return pts;
}
