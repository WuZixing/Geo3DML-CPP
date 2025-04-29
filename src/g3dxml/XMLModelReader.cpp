#include <g3dxml/XMLModelReader.h>
#include <g3dxml/XMLFeatureClassReader.h>
#include <geo3dml/Utils.h>

using namespace g3dxml;

const std::string XMLModelReader::Element = "Geo3DModel";
const std::string XMLModelReader::OldElement = "GeoModel";
const std::string XMLModelReader::Element_Name = "Name";
const std::string XMLModelReader::Element_Type = "Type";
const std::string XMLModelReader::Element_FeatureRelation = "Relation";
const std::string XMLModelReader::Element_Metadata = "Metadata";
const std::string XMLModelReader::Element_DateStamp = "dateStamp";
const std::string XMLModelReader::Element_Description = "Description";
const std::string XMLModelReader::Element_Version = "Version";
const std::string XMLModelReader::Element_ToolName = "ToolName";
const std::string XMLModelReader::Element_ToolVersion = "ToolVersion";
const std::string XMLModelReader::Element_TopicCategory = "TopicCategory";
const std::string XMLModelReader::Element_SpatialReferenceSystem = "SpatialReferenceSystem";
const std::string XMLModelReader::Element_CoordinateReferenceSystem = "CoordinateReferenceSystem";
const std::string XMLModelReader::Element_VerticalReferenceSystem = "VerticalReferenceSystem";

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
			} else if (geo3dml::IsiEqual(localName, Element_FeatureRelation)) {
				ReadFeatureRelation(reader, model);
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
		SetStatus(false, XMLReaderHelper::FormatErrorMessageAboutEncoding(fileEncoding, file));
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
	geo3dml::ModelMetadata meta;
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
			} else if (geo3dml::IsiEqual(localName, Element_TopicCategory)) {
				if (XMLReaderHelper::TextNode(reader, Element_TopicCategory, v)) {
					meta.SetTopicCategory(v);
				} else {
					SetStatus(false, v);
					break;
				}
			} else if (geo3dml::IsiEqual(localName, "CI_ResponsibleParty")) {
				ReadMetadataContact(reader, meta);
			} else if (geo3dml::IsiEqual(localName, Element_SpatialReferenceSystem)) {
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

bool XMLModelReader::ReadMetadataContact(xmlTextReaderPtr reader, geo3dml::ModelMetadata& meta) {
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

bool XMLModelReader::ReadMetadataSpatialCoordinateReference(xmlTextReaderPtr reader, geo3dml::ModelMetadata& meta) {
	std::string v;
	int status = xmlTextReaderRead(reader);
	while (status == 1) {
		const char* localName = (const char*)xmlTextReaderConstLocalName(reader);
		int nodeType = xmlTextReaderNodeType(reader);
		if (nodeType == XML_READER_TYPE_END_ELEMENT && geo3dml::IsiEqual(localName, Element_SpatialReferenceSystem)) {
			break;
		} else if (nodeType == XML_READER_TYPE_ELEMENT) {
			if (geo3dml::IsiEqual(localName, Element_CoordinateReferenceSystem)) {
				ReadMetadataCRS(reader, meta);
			} else if (geo3dml::IsiEqual(localName, Element_VerticalReferenceSystem)) {
				ReadMetadataVRS(reader, meta);
			}
		}
		status = xmlTextReaderRead(reader);
	}
	if (status != 1) {
		std::string err = XMLReaderHelper::FormatErrorMessageWithPosition(reader, "missing end element of " + Element_SpatialReferenceSystem);
		SetStatus(false, err);
	}
	return IsOK();
}

bool XMLModelReader::ReadMetadataCRS(xmlTextReaderPtr reader, geo3dml::ModelMetadata& meta) {
	std::string v;
	int status = xmlTextReaderRead(reader);
	while (status == 1) {
		const char* localName = (const char*)xmlTextReaderConstLocalName(reader);
		int nodeType = xmlTextReaderNodeType(reader);
		if (nodeType == XML_READER_TYPE_END_ELEMENT && geo3dml::IsiEqual(localName, Element_CoordinateReferenceSystem)) {
			break;
		} else if (geo3dml::IsiEqual(localName, "Identifier")) {
			if (XMLReaderHelper::TextNode(reader, "Identifier", v)) {
				meta.SetCoordRefSysID(v);
			} else {
				SetStatus(false, v);
				break;
			}
		} else if (geo3dml::IsiEqual(localName, "Parameter")) {
			if (XMLReaderHelper::TextNode(reader, "Parameter", v)) {
				meta.SetCoordRefSysParam(v);
			} else {
				SetStatus(false, v);
				break;
			}
		}
		status = xmlTextReaderRead(reader);
	}
	if (status != 1) {
		std::string err = XMLReaderHelper::FormatErrorMessageWithPosition(reader, "missing end element of " + Element_CoordinateReferenceSystem);
		SetStatus(false, err);
	}
	return IsOK();
}

bool XMLModelReader::ReadMetadataVRS(xmlTextReaderPtr reader, geo3dml::ModelMetadata& meta) {
	std::string v;
	int status = xmlTextReaderRead(reader);
	while (status == 1) {
		const char* localName = (const char*)xmlTextReaderConstLocalName(reader);
		int nodeType = xmlTextReaderNodeType(reader);
		if (nodeType == XML_READER_TYPE_END_ELEMENT && geo3dml::IsiEqual(localName, Element_VerticalReferenceSystem)) {
			break;
		} else if (geo3dml::IsiEqual(localName, "Category")) {
			if (XMLReaderHelper::TextNode(reader, "Category", v)) {
				meta.SetVerticalRefSysCategory(v);
			} else {
				SetStatus(false, v);
				break;
			}
		} else if (geo3dml::IsiEqual(localName, "ReferenceSystem")) {
			if (XMLReaderHelper::TextNode(reader, "ReferenceSystem", v)) {
				meta.SetVerticalRefSysValue(v);
			} else {
				SetStatus(false, v);
				break;
			}
		}
		status = xmlTextReaderRead(reader);
	}
	if (status != 1) {
		std::string err = XMLReaderHelper::FormatErrorMessageWithPosition(reader, "missing end element of " + Element_VerticalReferenceSystem);
		SetStatus(false, err);
	}
	return IsOK();
}

bool XMLModelReader::ReadMetadataDateStamp(xmlTextReaderPtr reader, geo3dml::ModelMetadata& meta) {
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

bool XMLModelReader::ReadFeatureRelation(xmlTextReaderPtr reader, geo3dml::Model* model) {
	int status = xmlTextReaderRead(reader);
	while (status == 1) {
		const char* localName = (const char*)xmlTextReaderConstLocalName(reader);
		int nodeType = xmlTextReaderNodeType(reader);
		if (nodeType == XML_READER_TYPE_END_ELEMENT && geo3dml::IsiEqual(localName, Element_FeatureRelation)) {
			break;
		} else if (geo3dml::IsiEqual(localName, "BoundaryRelation")) {
			geo3dml::FeatureRelation* boundaryRelation = new geo3dml::FeatureRelation(geo3dml::FeatureRelation::RelationType::BOUNDARY);
			if (boundaryRelation != nullptr) {
				if (ReadFeatureRelationContent(reader, "BoundaryRelation", boundaryRelation)) {
					model->AddFeatureRelation(boundaryRelation);
				} else {
					delete boundaryRelation;
					break;
				}
			}
		} else if (geo3dml::IsiEqual(localName, "ContactRelation")) {
			geo3dml::FeatureRelation* contactRelation = new geo3dml::FeatureRelation(geo3dml::FeatureRelation::RelationType::CONTACT);
			if (contactRelation != nullptr) {
				if (ReadFeatureRelationContent(reader, "ContactRelation", contactRelation)) {
					model->AddFeatureRelation(contactRelation);
				} else {
					delete contactRelation;
					break;
				}
			}
		} else if (geo3dml::IsiEqual(localName, "GeologicalHistory")) {
			geo3dml::FeatureRelation* geologicalHistory = new geo3dml::FeatureRelation(geo3dml::FeatureRelation::RelationType::GEOLOGICAL_HISTORY);
			if (geologicalHistory != nullptr) {
				if (ReadFeatureRelationContent(reader, "GeologicalHistory", geologicalHistory)) {
					model->AddFeatureRelation(geologicalHistory);
				} else {
					delete geologicalHistory;
					break;
				}
			}
		} else if (geo3dml::IsiEqual(localName, "GeologicalStructure")) {
			geo3dml::FeatureRelation* geologicalStructure = new geo3dml::FeatureRelation(geo3dml::FeatureRelation::RelationType::GEOLOGICAL_STRUCTURE);
			if (geologicalStructure != nullptr) {
				if (ReadFeatureRelationContent(reader, "GeologicalStructure", geologicalStructure)) {
					model->AddFeatureRelation(geologicalStructure);
				} else {
					delete geologicalStructure;
					break;
				}
			}
		} else if (geo3dml::IsiEqual(localName, "AggregationRelation")) {
			geo3dml::FeatureRelation* aggregationRelation = new geo3dml::FeatureRelation(geo3dml::FeatureRelation::RelationType::AGGREGATION);
			if (aggregationRelation != nullptr) {
				if (ReadFeatureRelationContent(reader, "AggregationRelation", aggregationRelation)) {
					model->AddFeatureRelation(aggregationRelation);
				} else {
					delete aggregationRelation;
					break;
				}
			}
		} else if (geo3dml::IsiEqual(localName, "IntrusiveRelation")) {
			geo3dml::FeatureRelation* instrusiveRelation = new geo3dml::FeatureRelation(geo3dml::FeatureRelation::RelationType::INTRUSIVE);
			if (instrusiveRelation != nullptr) {
				if (ReadFeatureRelationContent(reader, "IntrusiveRelation", instrusiveRelation)) {
					model->AddFeatureRelation(instrusiveRelation);
				} else {
					delete instrusiveRelation;
					break;
				}
			}
		} else if (geo3dml::IsiEqual(localName, "GeoFeatureRelation")) {
			geo3dml::FeatureRelation* featureRelation = new geo3dml::FeatureRelation(geo3dml::FeatureRelation::RelationType::GENERAL);
			if (featureRelation != nullptr) {
				if (ReadFeatureRelationContent(reader, "GeoFeatureRelation", featureRelation)) {
					model->AddFeatureRelation(featureRelation);
				} else {
					delete featureRelation;
					break;
				}
			}
		}
		status = xmlTextReaderRead(reader);
	}
	if (status != 1) {
		std::string err = XMLReaderHelper::FormatErrorMessageWithPosition(reader, "missing end element of " + Element_FeatureRelation);
		SetStatus(false, err);
	}
	return IsOK();
}

bool XMLModelReader::ReadFeatureRelationContent(xmlTextReaderPtr reader, const std::string& relationElemTag, geo3dml::FeatureRelation* featureRelation) {
	featureRelation->SetID(XMLReaderHelper::AttributeGMLID(reader));
	int status = xmlTextReaderRead(reader);
	while (status == 1) {
		const char* localName = (const char*)xmlTextReaderConstLocalName(reader);
		int nodeType = xmlTextReaderNodeType(reader);
		if (nodeType == XML_READER_TYPE_END_ELEMENT && geo3dml::IsiEqual(localName, relationElemTag)) {
			break;
		} else if (nodeType == XML_READER_TYPE_ELEMENT) {
			if (geo3dml::IsiEqual(localName, "name")) {
				std::string name;
				if (!XMLReaderHelper::TextNode(reader, "name", name)) {
					SetStatus(false, name);
					break;
				}
				featureRelation->SetName(name);
			} else if (geo3dml::IsiEqual(localName, "Source")) {
				if (!ReadSourceFeatureInRelation(reader, featureRelation)) {
					break;
				}
			} else if (geo3dml::IsiEqual(localName, "Targets")) {
				if (!ReadTargetFeaturesInRelation(reader, featureRelation)) {
					break;
				}
			}
		}
		status = xmlTextReaderRead(reader);
	}
	if (status != 1) {
		std::string err = XMLReaderHelper::FormatErrorMessageWithPosition(reader, "missing end element of " + relationElemTag);
		SetStatus(false, err);
	}
	return IsOK();
}

bool XMLModelReader::ReadSourceFeatureInRelation(xmlTextReaderPtr reader, geo3dml::FeatureRelation* featureRelation) {
	int status = xmlTextReaderRead(reader);
	while (status == 1) {
		const char* localName = (const char*)xmlTextReaderConstLocalName(reader);
		int nodeType = xmlTextReaderNodeType(reader);
		if (nodeType == XML_READER_TYPE_END_ELEMENT && geo3dml::IsiEqual(localName, "Source")) {
			break;
		} else if (nodeType == XML_READER_TYPE_ELEMENT) {
			if (geo3dml::IsiEqual(localName, "Feature")) {
				std::string featureId = XMLReaderHelper::AttributeIdInHref(reader);
				if (!featureId.empty()) {
					featureRelation->SetSourceFeatureId(featureId);
				} else {
					std::string err = XMLReaderHelper::FormatErrorMessageWithPosition(reader, "missing attribute of xlink:href");
					SetStatus(false, err);
					break;
				}
			} else if (geo3dml::IsiEqual(localName, "Role")) {
				std::string role;
				if (!XMLReaderHelper::TextNode(reader, "Role", role)) {
					SetStatus(false, role);
					break;
				}
				featureRelation->SetSourceRole(role);
			}
		}
		status = xmlTextReaderRead(reader);
	}
	if (status != 1) {
		std::string err = XMLReaderHelper::FormatErrorMessageWithPosition(reader, "missing end element of Source");
		SetStatus(false, err);
	}
	return IsOK();
}

bool XMLModelReader::ReadTargetFeaturesInRelation(xmlTextReaderPtr reader, geo3dml::FeatureRelation* featureRelation) {
	int status = xmlTextReaderRead(reader);
	while (status == 1) {
		const char* localName = (const char*)xmlTextReaderConstLocalName(reader);
		int nodeType = xmlTextReaderNodeType(reader);
		if (nodeType == XML_READER_TYPE_END_ELEMENT && geo3dml::IsiEqual(localName, "Targets")) {
			break;
		} else if (nodeType == XML_READER_TYPE_ELEMENT) {
			if (geo3dml::IsiEqual(localName, "Feature")) {
				std::string featureId = XMLReaderHelper::AttributeIdInHref(reader);
				if (!featureId.empty()) {
					featureRelation->AddTargetFeatureId(featureId);
				} else {
					std::string err = XMLReaderHelper::FormatErrorMessageWithPosition(reader, "missing attribute of xlink:href");
					SetStatus(false, err);
					break;
				}
			} else if (geo3dml::IsiEqual(localName, "Role")) {
				std::string role;
				if (!XMLReaderHelper::TextNode(reader, "Role", role)) {
					SetStatus(false, role);
					break;
				}
				featureRelation->SetTargetRole(role);
			}
		}
		status = xmlTextReaderRead(reader);
	}
	if (status != 1) {
		std::string err = XMLReaderHelper::FormatErrorMessageWithPosition(reader, "missing end element of Targets");
		SetStatus(false, err);
	}
	return IsOK();
}
