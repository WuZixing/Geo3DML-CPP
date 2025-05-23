#include <g3dxml/XMLFeatureTypeStyleReader.h>
#include <g3dxml/XMLStyleRuleReader.h>
#include <geo3dml/Utils.h>

using namespace g3dxml;

const std::string XMLFeatureTypeStyleReader::Element = "FeatureTypeStyle";

XMLFeatureTypeStyleReader::XMLFeatureTypeStyleReader(geo3dml::ObjectFactory* factory) {
	g3dFactory_ = factory;
}

XMLFeatureTypeStyleReader::~XMLFeatureTypeStyleReader() {
	g3dFactory_ = NULL;
}

geo3dml::FeatureTypeStyle* XMLFeatureTypeStyleReader::ReadFeatureTypeStyle(xmlTextReaderPtr reader) {
	geo3dml::FeatureTypeStyle* ftStyle = g3dFactory_->NewFeatureTypeStyle();
	int status = xmlTextReaderRead(reader);
	while (status == 1) {
		const char* localName = (const char*)xmlTextReaderConstLocalName(reader);
		int nodeType = xmlTextReaderNodeType(reader);
		if (nodeType == XML_READER_TYPE_END_ELEMENT && geo3dml::IsiEqual(localName, Element)) {
			break;
		} else if (nodeType == XML_READER_TYPE_ELEMENT) {
			if (geo3dml::IsiEqual(localName, XMLStyleRuleReader::Element)) {
				XMLStyleRuleReader ruleReader(g3dFactory_);
				geo3dml::StyleRule* rule = ruleReader.ReadStyleRule(reader);
				if (rule != NULL) {
					ftStyle->AddRule(rule);
				} else {
					SetStatus(false, ruleReader.Error());
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
		delete ftStyle;
		ftStyle = NULL;
	}
	return ftStyle;
}
