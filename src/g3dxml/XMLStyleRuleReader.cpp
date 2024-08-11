#include <g3dxml/XMLStyleRuleReader.h>
#include <geo3dml/StyleRuleEqualTo.h>
#include <g3dxml/XMLPointSymbolizerReader.h>
#include <g3dxml/XMLLineSymbolizerReader.h>
#include <g3dxml/XMLSurfaceSymbolizerReader.h>
#include <g3dxml/XMLGeoDiscreteCoverageSymbolizerReader.h>
#include <geo3dml/Utils.h>

using namespace g3dxml;

const std::string XMLStyleRuleReader::Element = "Rule";

XMLStyleRuleReader::XMLStyleRuleReader(geo3dml::ObjectFactory* factory) :
	Element_Filter("Filter"),
	Element_Filter_IsEqualTo("PropertyIsEqualTo") {
	g3dFactory_ = factory;
}

XMLStyleRuleReader::~XMLStyleRuleReader() {
	g3dFactory_ = NULL;
}

geo3dml::StyleRule* XMLStyleRuleReader::ReadStyleRule(xmlTextReaderPtr reader) {
	geo3dml::StyleRule* rule = NULL;
	geo3dml::Symbolizer* symbolizer = NULL;
	int status = xmlTextReaderRead(reader);
	while (status == 1) {
		const char* localName = (const char*)xmlTextReaderConstLocalName(reader);
		int nodeType = xmlTextReaderNodeType(reader);
		if (nodeType == XML_READER_TYPE_END_ELEMENT && geo3dml::IsiEqual(localName, Element)) {
			break;
		} else if (nodeType == XML_READER_TYPE_ELEMENT) {
			if (geo3dml::IsiEqual(localName, Element_Filter)) {
				rule = ReadFilter(reader);
				if (rule != NULL) {
					if (symbolizer != NULL) {
						rule->SetSymbolizer(symbolizer);
					}
				} else {
					break;
				}
			} else if (geo3dml::IsiEqual(localName, XMLPointSymbolizerReader::Element)) {
				XMLPointSymbolizerReader pointSymReader(g3dFactory_);
				symbolizer = pointSymReader.ReadPointSym(reader);
				if (symbolizer != NULL) {
					if (rule != NULL) {
						rule->SetSymbolizer(symbolizer);
					}
				} else {
					SetStatus(false, pointSymReader.Error());
					break;
				}
			} else if (geo3dml::IsiEqual(localName, XMLLineSymbolizerReader::Element)) {
				XMLLineSymbolizerReader lineSymReader(g3dFactory_);
				symbolizer = lineSymReader.ReadLineSym(reader);
				if (symbolizer != NULL) {
					if (rule != NULL) {
						rule->SetSymbolizer(symbolizer);
					}
				} else {
					SetStatus(false, lineSymReader.Error());
					break;
				}
			} else if (geo3dml::IsiEqual(localName, XMLSurfaceSymbolizerReader::Element)) {
				XMLSurfaceSymbolizerReader surfaceSymReader(g3dFactory_);
				symbolizer = surfaceSymReader.ReadSurfaceSym(reader);
				if (symbolizer != NULL) {
					if (rule != NULL) {
						rule->SetSymbolizer(symbolizer);
					}
				} else {
					SetStatus(false, surfaceSymReader.Error());
					break;
				}
			} else if (geo3dml::IsiEqual(localName, XMLGeoDiscreteCoverageSymbolizerReader::Element)) {
				XMLGeoDiscreteCoverageSymbolizerReader coverageSymReader(g3dFactory_);
				symbolizer = coverageSymReader.ReadCoverageSym(reader);
				if (symbolizer != NULL) {
					if (rule != NULL) {
						rule->SetSymbolizer(symbolizer);
					}
				} else {
					SetStatus(false, coverageSymReader.Error());
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
	if (IsOK()) {
		if (rule == NULL && symbolizer != NULL) {
			rule = new geo3dml::StyleRule();
			rule->SetSymbolizer(symbolizer);	// a symbolizer which matches any feature.
		}
	} else {
		if (rule != NULL) {
			delete rule;
			rule = NULL;
		} else {
			if (symbolizer != NULL) {
				delete symbolizer;
				symbolizer = NULL;
			}
		}
	}
	return rule;
}

geo3dml::StyleRule* XMLStyleRuleReader::ReadFilter(xmlTextReaderPtr reader) {
	geo3dml::StyleRule* rule = NULL;
	int status = xmlTextReaderRead(reader);
	while (status == 1) {
		const char* localName = (const char*)xmlTextReaderConstLocalName(reader);
		int nodeType = xmlTextReaderNodeType(reader);
		if (nodeType == XML_READER_TYPE_END_ELEMENT && geo3dml::IsiEqual(localName, Element_Filter)) {
			break;
		} else if (nodeType == XML_READER_TYPE_ELEMENT) {
			if (geo3dml::IsiEqual(localName, Element_Filter_IsEqualTo)) {
				rule = ReadEqualToFilter(reader);
				if (rule == NULL) {
					break;
				}
			}
			/// TODO: read filters of other type.
		}
		status = xmlTextReaderRead(reader);
	}
	if (status != 1) {
		std::string err = XMLReaderHelper::FormatErrorMessageWithPosition(reader, "missing end element of " + Element_Filter);
		SetStatus(false, err);
	}
	return rule;
}

geo3dml::StyleRule* XMLStyleRuleReader::ReadEqualToFilter(xmlTextReaderPtr reader) {
	geo3dml::StyleRuleEqualTo* eqRule = new geo3dml::StyleRuleEqualTo();
	int status = xmlTextReaderRead(reader);
	while (status == 1) {
		const char* localName = (const char*)xmlTextReaderConstLocalName(reader);
		int nodeType = xmlTextReaderNodeType(reader);
		if (nodeType == XML_READER_TYPE_END_ELEMENT && geo3dml::IsiEqual(localName, Element_Filter_IsEqualTo)) {
			break;
		} else if (nodeType == XML_READER_TYPE_ELEMENT) {
			if (geo3dml::IsiEqual(localName, "PropertyName")) {
				std::string v;
				if (XMLReaderHelper::TextNode(reader, "PropertyName", v)) {
					eqRule->SetFieldName(v);
				} else {
					SetStatus(false, v);
					break;
				}
			} else if (geo3dml::IsiEqual(localName, "Literal")) {
				std::string v;
				if (XMLReaderHelper::TextNode(reader, "Literal", v)) {
					eqRule->SetValueLiteral(v);
				} else {
					SetStatus(false, v);
					break;
				}
			}
		}
		status = xmlTextReaderRead(reader);
	}
	if (status != 1) {
		std::string err = XMLReaderHelper::FormatErrorMessageWithPosition(reader, "missing end element of " + Element_Filter_IsEqualTo);
		SetStatus(false, err);
	}
	if (!IsOK()) {
		delete eqRule;
		eqRule = NULL;
	}
	return eqRule;
}
