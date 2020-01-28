#include <g3dxml/XMLGeoDiscreteCoverageSymbolizerReader.h>
#include <geo3dml/Utils.h>

using namespace g3dxml;

std::string XMLGeoDiscreteCoverageSymbolizerReader::Element = "GeoDiscreteCoverageSymbolizer";


XMLGeoDiscreteCoverageSymbolizerReader::XMLGeoDiscreteCoverageSymbolizerReader(geo3dml::ObjectFactory* factory) {
	g3dFactory_ = factory;
}

XMLGeoDiscreteCoverageSymbolizerReader::~XMLGeoDiscreteCoverageSymbolizerReader() {
	g3dFactory_ = NULL;
}

geo3dml::GeoDiscreteCoverageSymbolizer* XMLGeoDiscreteCoverageSymbolizerReader::ReadCoverageSym(xmlTextReaderPtr reader) {
	geo3dml::GeoDiscreteCoverageSymbolizer* coverageSym = g3dFactory_->NewGeoDiscreteCoverageSymbolizer();
	int status = xmlTextReaderRead(reader);
	while (status == 1) {
		const char* localName = (const char*)xmlTextReaderConstLocalName(reader);
		int nodeType = xmlTextReaderNodeType(reader);
		if (nodeType == XML_READER_TYPE_END_ELEMENT && geo3dml::IsiEqual(localName, Element)) {
			break;
		} else if (nodeType == XML_READER_TYPE_ELEMENT) {
			;
		}
		status = xmlTextReaderRead(reader);
	}
	if (status != 1) {
		std::string err = XMLReaderHelper::FormatErrorMessageWithPosition(reader, "missing end element of " + Element);
		SetStatus(false, err);
	}
	if (!IsOK()) {
		delete coverageSym;
		coverageSym = NULL;
	}
	return coverageSym;
}
