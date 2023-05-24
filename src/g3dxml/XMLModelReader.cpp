#include <g3dxml/XMLModelReader.h>
#include <g3dxml/XMLFeatureClassReader.h>
#include <geo3dml/Utils.h>

using namespace g3dxml;

std::string XMLModelReader::Element = "Geo3DModel";
const std::string XMLModelReader::OldElement = "GeoModel";
const std::string XMLModelReader::Element_Name = "Name";
const std::string XMLModelReader::Element_Type = "Type";
const std::string XMLModelReader::Element_Metadata = "Metadata";
const std::string XMLModelReader::Element_DateStamp = "Date";
const std::string XMLModelReader::Element_Description = "Description";
const std::string XMLModelReader::Element_Version = "Version";
const std::string XMLModelReader::Element_ToolName = "ToolName";
const std::string XMLModelReader::Element_ToolVersion = "ToolVersion";

bool XMLModelReader::IsModelElementName(const std::string& name) {
	if (geo3dml::IsiEqual(name, Element)) {
		return true;
	} else if (geo3dml::IsiEqual(name, OldElement)) {
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
	std::string modelId = XMLReaderHelper::Attribute(reader, "ID");
	if (modelId.empty()) {
		modelId = geo3dml::Object::NewID();
	}
	model->SetID(modelId);
	int status = xmlTextReaderRead(reader);
	while (status == 1) {
		const char* localName = (const char*)xmlTextReaderConstLocalName(reader);
		int nodeType = xmlTextReaderNodeType(reader);
		/// TODO: parse feature relationship.
		if (nodeType == XML_READER_TYPE_END_ELEMENT && IsModelElementName(localName)) {
			break;
		} else if (nodeType == XML_READER_TYPE_ELEMENT) {
			if (geo3dml::IsiEqual(localName, Element_Name)) {
				std::string v;
				if (!XMLReaderHelper::TextNode(reader, Element_Name, v)) {
					SetStatus(false, v);
					break;
				}
				model->SetName(v);
			} else if (geo3dml::IsiEqual(localName, Element_Type)) {
				std::string v;
				if (!XMLReaderHelper::TextNode(reader, Element_Type, v)) {
					SetStatus(false, v);
					break;
				}
				model->SetType(geo3dml::Model::NameToModelType(v));
			} else if (geo3dml::IsiEqual(localName, Element_Metadata)) {
				ReadMetadata(reader, model);
			} else if (geo3dml::IsiEqual(localName, XMLFeatureClassReader::Element)) {
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

bool XMLModelReader::ReadMetadata(xmlTextReaderPtr reader, geo3dml::Model* model) {
	std::string v;
	int status = xmlTextReaderRead(reader);
	while (status == 1) {
		const char* localName = (const char*)xmlTextReaderConstLocalName(reader);
		int nodeType = xmlTextReaderNodeType(reader);
		if (nodeType == XML_READER_TYPE_END_ELEMENT && geo3dml::IsiEqual(localName, Element_Metadata)) {
			break;
		} else if (nodeType == XML_READER_TYPE_ELEMENT) {
			if (geo3dml::IsiEqual(localName, Element_DateStamp)) {
				if (XMLReaderHelper::TextNode(reader, Element_DateStamp, v)) {
					model->SetDateStamp(v);
				} else {
					SetStatus(false, v);
					break;
				}
			} else if (geo3dml::IsiEqual(localName, Element_Description)) {
				if (XMLReaderHelper::TextNode(reader, Element_Description, v)) {
					model->SetDescription(v);
				} else {
					SetStatus(false, v);
					break;
				}
			} else if (geo3dml::IsiEqual(localName, Element_Version)) {
				if (XMLReaderHelper::TextNode(reader, Element_Version, v)) {
					model->SetVersion(v);
				} else {
					SetStatus(false, v);
					break;
				}
			} else if (geo3dml::IsiEqual(localName, Element_ToolName)) {
				if (XMLReaderHelper::TextNode(reader, Element_ToolName, v)) {
					model->SetToolName(v);
				} else {
					SetStatus(false, v);
					break;
				}
			} else if (geo3dml::IsiEqual(localName, Element_ToolVersion)) {
				if (XMLReaderHelper::TextNode(reader, Element_ToolVersion, v)) {
					model->SetToolVersion(v);
				} else {
					SetStatus(false, v);
					break;
				}
			}
		}
		status = xmlTextReaderRead(reader);
	}
	if (status != 1) {
		std::string err = XMLReaderHelper::FormatErrorMessageWithPosition(reader, "missing end element of " + Element_Metadata);
		SetStatus(false, err);
	}
	return IsOK();
}
