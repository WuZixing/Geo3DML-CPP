#include <g3dxml/XMLModelReader.h>
#include <g3dxml/XMLFeatureClassReader.h>
#include <geo3dml/Utils.h>

using namespace g3dxml;

std::string XMLModelReader::Element = "Geo3DModel";
const std::string XMLModelReader::OldElement = "GeoModel";
const std::string XMLModelReader::Element_Name = "Name";
const std::string XMLModelReader::Element_Type = "Type";
const std::string XMLModelReader::Element_Metadata = "Metadata";
const std::string XMLModelReader::Element_DateStamp = "dateStamp";
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
	geo3dml::Metadata meta;
	int status = xmlTextReaderRead(reader);
	while (status == 1) {
		const char* localName = (const char*)xmlTextReaderConstLocalName(reader);
		int nodeType = xmlTextReaderNodeType(reader);
		if (nodeType == XML_READER_TYPE_END_ELEMENT && geo3dml::IsiEqual(localName, Element_Metadata)) {
			break;
		} else if (nodeType == XML_READER_TYPE_ELEMENT) {
			if (geo3dml::IsiEqual(localName, Element_DateStamp)) {
				if (!ReadMetadataDateStamp(reader, meta)) {
					break;
				}
			} else if (geo3dml::IsiEqual(localName, Element_Description)) {
				if (XMLReaderHelper::TextNode(reader, Element_Description, v)) {
					meta.SetDescription(v);
				} else {
					SetStatus(false, v);
					break;
				}
			} else if (geo3dml::IsiEqual(localName, Element_Version)) {
				if (XMLReaderHelper::TextNode(reader, Element_Version, v)) {
					meta.SetVersion(v);
				} else {
					SetStatus(false, v);
					break;
				}
			} else if (geo3dml::IsiEqual(localName, Element_ToolName)) {
				if (XMLReaderHelper::TextNode(reader, Element_ToolName, v)) {
					meta.SetToolName(v);
				} else {
					SetStatus(false, v);
					break;
				}
			} else if (geo3dml::IsiEqual(localName, Element_ToolVersion)) {
				if (XMLReaderHelper::TextNode(reader, Element_ToolVersion, v)) {
					meta.SetToolVersion(v);
				} else {
					SetStatus(false, v);
					break;
				}
			} else if (geo3dml::IsiEqual(localName, "CI_ResponsibleParty")) {
				ReadMetadataContact(reader, meta);
			} else if (geo3dml::IsiEqual(localName, "CoordinateReferenceSystem")) {
				ReadMetadataSpatialCoordinateReference(reader, meta);
			}
		}
		status = xmlTextReaderRead(reader);
	}
	if (status != 1) {
		std::string err = XMLReaderHelper::FormatErrorMessageWithPosition(reader, "missing end element of " + Element_Metadata);
		SetStatus(false, err);
	}
	model->SetMetadata(meta);
	return IsOK();
}

bool XMLModelReader::ReadMetadataContact(xmlTextReaderPtr reader, geo3dml::Metadata& meta) {
	std::string v;
	int status = xmlTextReaderRead(reader);
	while (status == 1) {
		const char* localName = (const char*)xmlTextReaderConstLocalName(reader);
		int nodeType = xmlTextReaderNodeType(reader);
		if (nodeType == XML_READER_TYPE_END_ELEMENT && geo3dml::IsiEqual(localName, "CI_ResponsibleParty")) {
			break;
		} else if (nodeType == XML_READER_TYPE_ELEMENT) {
			if (geo3dml::IsiEqual(localName, "individualName")) {
				v = ReadCharacterString(reader, "individualName");
				if (IsOK()) {
					meta.SetResponsibleIndividualName(v);
				} else {
					break;
				}
			} else if (geo3dml::IsiEqual(localName, "organisationName")) {
				v = ReadCharacterString(reader, "organisationName");
				if (IsOK()) {
					meta.SetResponsibleOrganisationName(v);
				} else {
					break;
				}
			} else if (geo3dml::IsiEqual(localName, "CI_Telephone")) {
				v = ReadCharacterString(reader, "CI_Telephone");
				if (IsOK()) {
					meta.SetContactPhone(v);
				} else {
					break;
				}
			} else if (geo3dml::IsiEqual(localName, "deliveryPoint")) {
				v = ReadCharacterString(reader, "deliveryPoint");
				if (IsOK()) {
					meta.SetContactAddress(v);
				} else {
					break;
				}
			} else if (geo3dml::IsiEqual(localName, "electronicMailAddress")) {
				v = ReadCharacterString(reader, "electronicMailAddress");
				if (IsOK()) {
					meta.SetContactEmail(v);
				} else {
					break;
				}
			}
		}
		status = xmlTextReaderRead(reader);
	}
	if (status != 1) {
		std::string err = XMLReaderHelper::FormatErrorMessageWithPosition(reader, "missing end element of CI_ResponsibleParty");
		SetStatus(false, err);
	}
	return IsOK();
}

std::string XMLModelReader::ReadCharacterString(xmlTextReaderPtr reader, const std::string& parentNode) {
	std::string v;
	int status = xmlTextReaderRead(reader);
	while (status == 1) {
		const char* localName = (const char*)xmlTextReaderConstLocalName(reader);
		int nodeType = xmlTextReaderNodeType(reader);
		if (nodeType == XML_READER_TYPE_END_ELEMENT && geo3dml::IsiEqual(localName, parentNode)) {
			break;
		} else if (geo3dml::IsiEqual(localName, "CharacterString")) {
			if (!XMLReaderHelper::TextNode(reader, "CharacterString", v)) {
				SetStatus(false, v);
				break;
			}
		}
		status = xmlTextReaderRead(reader);
	}
	if (status != 1) {
		std::string err = XMLReaderHelper::FormatErrorMessageWithPosition(reader, "missing end element of " + parentNode);
		SetStatus(false, err);
	}
	return v;
}

bool XMLModelReader::ReadMetadataSpatialCoordinateReference(xmlTextReaderPtr reader, geo3dml::Metadata& meta) {
	std::string v;
	int status = xmlTextReaderRead(reader);
	while (status == 1) {
		const char* localName = (const char*)xmlTextReaderConstLocalName(reader);
		int nodeType = xmlTextReaderNodeType(reader);
		if (nodeType == XML_READER_TYPE_END_ELEMENT && geo3dml::IsiEqual(localName, "CoordinateReferenceSystem")) {
			break;
		} else if (nodeType == XML_READER_TYPE_ELEMENT) {
			if (geo3dml::IsiEqual(localName, "CoordinateReferenceSystemIdentifier")) {
				if (XMLReaderHelper::TextNode(reader, "CoordinateReferenceSystemIdentifier", v)) {
					meta.SetCoordRefSysID(v);
				} else {
					SetStatus(false, v);
					break;
				}
			} else if (geo3dml::IsiEqual(localName, "CoordinateSystemType")) {
				if (XMLReaderHelper::TextNode(reader, "CoordinateSystemType", v)) {
					meta.SetCoordSysType(v);
				} else {
					SetStatus(false, v);
					break;
				}
			} else if (geo3dml::IsiEqual(localName, "CoordinateSystemIdentifier")) {
				if (XMLReaderHelper::TextNode(reader, "CoordinateSystemIdentifier", v)) {
					meta.SetCoordSysID(v);
				} else {
					SetStatus(false, v);
					break;
				}
			}
		}
		status = xmlTextReaderRead(reader);
	}
	if (status != 1) {
		std::string err = XMLReaderHelper::FormatErrorMessageWithPosition(reader, "missing end element of CoordinateReferenceSystem");
		SetStatus(false, err);
	}
	return IsOK();
}

bool XMLModelReader::ReadMetadataDateStamp(xmlTextReaderPtr reader, geo3dml::Metadata& meta) {
	std::string v;
	int status = xmlTextReaderRead(reader);
	while (status == 1) {
		const char* localName = (const char*)xmlTextReaderConstLocalName(reader);
		int nodeType = xmlTextReaderNodeType(reader);
		if (nodeType == XML_READER_TYPE_END_ELEMENT && geo3dml::IsiEqual(localName, Element_DateStamp)) {
			break;
		} else if (nodeType == XML_READER_TYPE_ELEMENT) {
			if (geo3dml::IsiEqual(localName, "Date")) {
				if (XMLReaderHelper::TextNode(reader, "Date", v)) {
					meta.SetDateStamp(v, false);
				} else {
					SetStatus(false, v);
					break;
				}
			} else if (geo3dml::IsiEqual(localName, "DateTime")) {
				if (XMLReaderHelper::TextNode(reader, "DateTime", v)) {
					meta.SetDateStamp(v, true);
				} else {
					SetStatus(false, v);
					break;
				}
			}
		}
		status = xmlTextReaderRead(reader);
	}
	if (status != 1) {
		std::string err = XMLReaderHelper::FormatErrorMessageWithPosition(reader, "missing end element of " + Element_DateStamp);
		SetStatus(false, err);
	}
	return IsOK();
}
