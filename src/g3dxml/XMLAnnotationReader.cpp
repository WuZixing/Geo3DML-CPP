#include <g3dxml/XMLAnnotationReader.h>
#include <geo3dml/Utils.h>

using namespace g3dxml;

std::string XMLAnnotationReader::Element = "GeoAnnotation";
std::string XMLAnnotationReader::Element_Pos = "pos";
std::string XMLAnnotationReader::Element_Label = "Label";

XMLAnnotationReader::XMLAnnotationReader(geo3dml::ObjectFactory* factory) {
	g3dFactory_ = factory;
}

XMLAnnotationReader::~XMLAnnotationReader() {

}

geo3dml::Annotation* XMLAnnotationReader::ReadAnnotation(xmlTextReaderPtr reader) {
	geo3dml::Annotation* annotation = g3dFactory_->NewAnnotation();
	annotation->SetID(XMLReaderHelper::AttributeGMLID(reader));
	int status = xmlTextReaderRead(reader);
	while (status == 1) {
		const char* localName = (const char*)xmlTextReaderConstLocalName(reader);
		int nodeType = xmlTextReaderNodeType(reader);
		if (nodeType == XML_READER_TYPE_END_ELEMENT && geo3dml::IsiEqual(localName, Element)) {
			break;
		} else if (nodeType == XML_READER_TYPE_ELEMENT) {
			if (geo3dml::IsiEqual(localName, Element_Pos)) {
				if (!ReadPos(reader, annotation)) {
					break;
				}
			} else if (geo3dml::IsiEqual(localName, Element_Label)) {
				if (!ReadLabel(reader, annotation)) {
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
		delete annotation;
		annotation = NULL;
	}
	return annotation;
}

bool XMLAnnotationReader::ReadPos(xmlTextReaderPtr reader, geo3dml::Annotation* annotation) {
	std::string strSrsDimension = XMLReaderHelper::Attribute(reader, "srsDimension");
	int srsDimension = atoi(strSrsDimension.c_str());
	std::string posList;
	if (!XMLReaderHelper::TextNode(reader, Element_Pos, posList)) {
		SetStatus(false, posList);
		return false;
	}
	char* end = NULL;
	double x = strtod(posList.c_str(), &end);
	double y = strtod(end, &end);
	double z = strtod(end, NULL);
	annotation->AddPoint(x, y, z);
	return true;
}

bool XMLAnnotationReader::ReadLabel(xmlTextReaderPtr reader, geo3dml::Annotation* annotation) {
	std::string index = XMLReaderHelper::Attribute(reader, "IndexNo");
	long idx = strtol(index.c_str(), NULL, 10);
	std::string label;
	if (XMLReaderHelper::TextNode(reader, Element_Label, label)) {
		annotation->SetLabelOfPointAt(idx, label);
		return true;
	} else {
		SetStatus(false, label);
		return false;
	}
}