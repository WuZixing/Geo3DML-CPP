#include <g3dxml/XMLModelReader.h>
#include <g3dxml/XMLFeatureClassReader.h>

using namespace g3dxml;

std::string XMLModelReader::OldElement = "GeoModel";
std::string XMLModelReader::Element = "Geo3DModel";
std::string XMLModelReader::Element_Name = "Name";
std::string XMLModelReader::Element_Type = "Type";

bool XMLModelReader::IsModelElementName(const std::string& name) {
	if (_stricmp(name.c_str(), Element.c_str()) == 0) {
		return true;
	} else if (_stricmp(name.c_str(), OldElement.c_str()) == 0) {
		return true;
	} else {
		return false;
	}
}

XMLModelReader::XMLModelReader(geo3dml::ObjectFactory* factory) {
	g3dFactory_ = factory;
}

XMLModelReader::~XMLModelReader() {
	g3dFactory_ = NULL;
}

geo3dml::Model* XMLModelReader::ReadModel(xmlTextReaderPtr reader) {
	geo3dml::Model* model = g3dFactory_->NewModel();
	model->SetID(XMLReaderHelper::Attribute(reader, "ID"));
	int status = xmlTextReaderRead(reader);
	while (status == 1) {
		const char* localName = (const char*)xmlTextReaderConstLocalName(reader);
		int nodeType = xmlTextReaderNodeType(reader);
		/// TODO: parse metadata, feature relationship.
		if (nodeType == XML_READER_TYPE_END_ELEMENT && IsModelElementName(localName)) {
			break;
		} else if (nodeType == XML_READER_TYPE_ELEMENT) {
			if (_stricmp(localName, Element_Name.c_str()) == 0) {
				std::string v;
				if (!XMLReaderHelper::TextNode(reader, Element_Name, v)) {
					SetStatus(false, v);
					break;
				}
				model->SetName(v);
			} else if (_stricmp(localName, Element_Type.c_str()) == 0) {
				std::string v;
				if (!XMLReaderHelper::TextNode(reader, Element_Type, v)) {
					SetStatus(false, v);
					break;
				}
				model->SetType(geo3dml::Model::NameToModelType(v));
			} else if (_stricmp(localName, XMLFeatureClassReader::Element.c_str()) == 0) {
				XMLFeatureClassReader fcReader(g3dFactory_);
				geo3dml::FeatureClass* featureClass = fcReader.ReadFeatureClass(reader);
				if (featureClass != NULL) {
					model->AddFeatureClass(featureClass);
				} else if (!fcReader.IsOK()) {
					SetStatus(false, fcReader.Error());
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
		delete model;
		model = NULL;
	}
	return model;
}

geo3dml::Model* XMLModelReader::LoadFromFile(const std::string& file) {
	std::string fileEncoding = XMLReaderHelper::DectectFileEncoding(file);
	if (!XMLReaderHelper::IsUTF8(fileEncoding)) {
		SetStatus(false, "unsupported encoding " + fileEncoding + " of file " + file);
		return NULL;
	}
	geo3dml::Model* model = NULL;
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
			if (IsModelElementName(localName)) {
				model = ReadModel(reader);
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
	return model;
}