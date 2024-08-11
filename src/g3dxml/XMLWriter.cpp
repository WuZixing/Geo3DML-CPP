#include <g3dxml/XMLWriter.h>
#include <g3dxml/XMLFeatureClassWriter.h>
#include <g3dxml/XMLLayerWriter.h>
#include <libxml/xmlreader.h>

using namespace g3dxml;

XMLWriter::XMLWriter() :
	NS_xi("xmlns:xi=\"http://www.w3.org/2001/XInclude\""),
	NS_xsi("xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\""),
	xsi_SchemaLocation("xsi:schemaLocation=\"http://www.cgs.gov.cn/geo3dml\""),
	NS_gml("xmlns:gml=\"http://www.opengis.net/gml/3.2\""),
	NS_swe("xmlns:swe=\"http://www.opengis.net/swe/2.0\""),
	NS_gco("xmlns:gco=\"http://www.isotc211.org/2005/gco\""),
	NS_gmd("xmlns:gmd=\"http://www.isotc211.org/2005/gmd\""),
	NS_xlink("xmlns:xlink=\"http://www.w3.org/1999/xlink\""),
	NS_gmlcov("xmlns:gmlcov=\"http://www.opengis.net/gmlcov/1.0\""),
	NS_ogc("xmlns:ogc=\"http://www.opengis.net/ogc\""),
	NS_se("xmlns:se=\"http://www.opengis.net/se\"") {
}

XMLWriter::~XMLWriter() {

}

bool XMLWriter::Write(geo3dml::Project* project, const std::string& xmlFilePath, SchemaVersion v) {
#if defined(_WIN32)
	char primaryPathSeperator = '\\';
	char secondaryPathSeperator = '/';	// Qt uses '/' as path seperator on windows.
#else
	char primaryPathSeperator = '/';
	char secondaryPathSeperator = '\\';
#endif
	size_t pos = xmlFilePath.find_last_of(primaryPathSeperator);
	if (pos == std::string::npos) {
		pos = xmlFilePath.find_last_of(secondaryPathSeperator);
	}
	if (pos != std::string::npos) {
		projectDirectory_ = xmlFilePath.substr(0, pos + 1);
	} else {
		projectDirectory_ = "";
	}
	std::ofstream xmlFile;
	OpenXMLFileForOutput(xmlFilePath, xmlFile);
	return Write(project, xmlFile, v);
}

bool XMLWriter::Write(geo3dml::Model* model, const std::string& xmlFilePath, SchemaVersion v) {
	std::ofstream xmlFile;
	OpenXMLFileForOutput(xmlFilePath, xmlFile);
	return Write(model, xmlFile, v);
}

bool XMLWriter::Write(geo3dml::Map* map, const std::string& xmlFilePath, SchemaVersion v) {
	std::ofstream xmlFile;
	OpenXMLFileForOutput(xmlFilePath, xmlFile);
	return Write(map, xmlFile, v);
}

bool XMLWriter::Write(geo3dml::Model* model, std::ostream& output, SchemaVersion v) {
	WriteXMLDeclaration(output);
	output << "<geo3dml:Geo3DModel " << NSGeo3DML(v) << " " << NSDefault(v) << std::endl
		<< NS_gml << std::endl
		<< NS_swe << std::endl
		<< NS_gco << std::endl
		<< NS_gmd << std::endl
		<< NS_xsi << std::endl
		<< NS_xlink << std::endl
		<< NS_gmlcov << std::endl
		<< xsi_SchemaLocation << std::endl
		<< "ID=\"" << model->GetID() << "\">" << std::endl;
	output << "<Name>" << model->GetName() << "</Name>" << std::endl;
	output << "<Type>" << geo3dml::Model::ModelTypeToName(model->GetType()) << "</Type>" << std::endl;
	const geo3dml::ModelMetadata& meta = model->GetMetadata();
	output << "<Metadata>" << std::endl;
	WriteContactOfMetadata(&meta, output);
	bool isDateTime = false;
	const std::string& dateStamp = meta.GetDateStamp(isDateTime);
	output << "<gmd:dateStamp>" << std::endl;
	if (isDateTime) {
		output << "<gco:DateTime>" << dateStamp << "</gco:DateTime>" << std::endl;
	} else {
		output << "<gco:Date>" << dateStamp << "</gco:Date>" << std::endl;
	}
	output << "</gmd:dateStamp>" << std::endl;
	output << "<Description>" << meta.GetDescription() << "</Description>" << std::endl
		<< "<Version>" << meta.GetVersion() << "</Version>" << std::endl
		<< "<SpatialReferenceSystem>" << std::endl
		<< "<CoordinateReferenceSystem>" << std::endl
		<< "<Identifier>" << meta.GetCoordRefSysID() << "</Identifier>" << std::endl
		<< "<Parameter>" << meta.GetCoordRefSysParam() << "</Parameter>" << std::endl
		<< "</CoordinateReferenceSystem>" << std::endl
		<< "<VerticalReferenceSystem>" << std::endl
		<< "<Category>" << meta.GetVerticalRefSysCategory() << "</Category>" << std::endl
		<< "<ReferenceSystem>" << meta.GetVerticalRefSysValue() << "</ReferenceSystem>" << std::endl
		<< "</VerticalReferenceSystem>" << std::endl
		<< "</SpatialReferenceSystem>" << std::endl
		<< "<ToolName>" << meta.GetToolName() << "</ToolName>" << std::endl
		<< "<ToolVersion>" << meta.GetToolVersion() << "</ToolVersion>" << std::endl;
	if (v != SchemaVersion::Schema_1_0) {
		output << "<TopicCategory>" << meta.GetTopicCategory() << "</TopicCategory>" << std::endl;
	}
	output << "</Metadata>" << std::endl;
	int featureClassNumber = model->GetFeatureClassCount();
	if (featureClassNumber > 0) {
		output << "<FeatureClasses>" << std::endl;
		for (int i = 0; i < featureClassNumber; ++i) {
			XMLFeatureClassWriter fcWriter;
			if (!fcWriter.Write(model->GetFeatureClassAt(i), output, v)) {
				SetStatus(false, fcWriter.Error());
				break;
			}
		}
		output << "</FeatureClasses>" << std::endl;
	}
	output << "</geo3dml:Geo3DModel>" << std::endl;
	return IsOK();
}

bool XMLWriter::Write(geo3dml::Project* project, std::ostream& output, SchemaVersion v) {
	WriteXMLDeclaration(output);
	output << "<geo3dml:Geo3DProject " << NSGeo3DML(v) << " " << NSDefault(v) << std::endl
		<< NS_xi << std::endl
		<< NS_xsi << std::endl
		<< xsi_SchemaLocation << ">" << std::endl;
	output << "<Name>" << project->GetName() << "</Name>" << std::endl;
	const geo3dml::ProjectMetadata& meta = project->GetMetadata();
	if (v == SchemaVersion::Schema_1_0) {
		output << "<Description>" << meta.GetDescription() << "</Description>" << std::endl;
	} else {
		if (!meta.IsEmpty()) {
			output << "<Metadata>" << std::endl
				<< "<Description>" << meta.GetDescription() << "</Description>" << std::endl;
			if (!meta.IsProjectInfoEmpty()) {
				output << "<ProjectInfo>" << std::endl
					<< "<Name>" << meta.GetProjectName() << "</Name>" << std::endl
					<< "<Code>" << meta.GetProjectCode() << "</Code>" << std::endl
					<< "<StartDate>" << meta.GetStartDate() << "</StartDate>" << std::endl
					<< "<CompletedDate>" << meta.GetCompleteDate() << "</CompletedDate>" << std::endl
					<< "<Contractor>" << meta.GetContractor() << "</Contractor>" << std::endl
					<< "</ProjectInfo>" << std::endl;
			}
			WriteContactOfMetadata(&meta, output);
			output << "</Metadata>" << std::endl;
		}
	}
	int modelNumber = project->GetModelCount();
	if (modelNumber > 0) {
		output << "<Models>" << std::endl;
		for (int m = 0; m < modelNumber; ++m) {
			geo3dml::Model* model = project->GetModelAt(m);
			std::string modelFileName = model->GetName() + "_model.xml";
			std::ofstream modelFile;
			OpenXMLFileForOutput(projectDirectory_ + modelFileName, modelFile);
			Write(model, modelFile, v);
			output << "<Model>" << "<xi:include href=\"" << modelFileName << "\" />" << "</Model>" << std::endl;
			if (!IsOK()) {
				break;
			}
		}
		output << "</Models>" << std::endl;
	}
	if (IsOK()) {
		int mapNumber = project->GetMapCount();
		if (mapNumber > 0) {
			output << "<Maps>" << std::endl;
			for (int m = 0; m < mapNumber; ++m) {
				geo3dml::Map* map = project->GetMapAt(m);
				std::string mapFileName = map->GetName() + "_map.xml";
				std::ofstream mapFile;
				OpenXMLFileForOutput(projectDirectory_ + mapFileName, mapFile);
				Write(map, mapFile, v);
				output << "<Map>" << "<xi:include href=\"" << mapFileName << "\" />" << "</Map>" << std::endl;
				if (!IsOK()) {
					break;
				}
			}
			output << "</Maps>" << std::endl;
		}
	}
	
	output << "</geo3dml:Geo3DProject>" << std::endl;
	return IsOK();
}

bool XMLWriter::Write(geo3dml::Map* map, std::ostream& output, SchemaVersion v) {
	WriteXMLDeclaration(output);
	output << "<geo3dml:Geo3DMap " << NSGeo3DML(v) << " " << NSDefault(v) << std::endl
		<< NS_gml << std::endl
		<< NS_xlink << std::endl
		<< NS_ogc << std::endl
		<< NS_se << std::endl
		<< NS_xsi << std::endl
		<< xsi_SchemaLocation << std::endl
		<< "ID=\"" << map->GetID() << "\">" << std::endl;
	output << "<Name>" << map->GetName() << "</Name>" << std::endl
		<< "<Description>" << map->GetDescription() << "</Description>" << std::endl;
	int layerNumber = map->GetLayerCount();
	if (layerNumber > 0) {
		output << "<Layers>" << std::endl;
		for (int i = 0; i < layerNumber; ++i) {
			geo3dml::Layer* layer = map->GetLayerAt(i);
			XMLLayerWriter layerWriter;
			if (!layerWriter.Write(layer, output, v)) {
				SetStatus(false, layerWriter.Error());
				break;
			}
		}
		output << "</Layers>" << std::endl;
	}
	output << "</geo3dml:Geo3DMap>" << std::endl;
	return IsOK();
}

void XMLWriter::WriteContactOfMetadata(const geo3dml::AbstractMetadata* metadata, std::ostream& output) {
	if (metadata->IsContactEmpty()) {
		return;
	}
	output << "<gmd:contact>" << std::endl
		<< "<gmd:CI_ResponsibleParty>" << std::endl
		<< "<gmd:individualName>" << std::endl
		<< "<gco:CharacterString>" << metadata->GetResponsibleIndividualName() << "</gco:CharacterString>" << std::endl
		<< "</gmd:individualName>" << std::endl
		<< "<gmd:organisationName>" << std::endl
		<< "<gco:CharacterString>" << metadata->GetResponsibleOrganisationName() << "</gco:CharacterString>" << std::endl
		<< "</gmd:organisationName>" << std::endl
		<< "<gmd:contactInfo>" << std::endl
		<< "<gmd:CI_Contact>" << std::endl
		<< "<gmd:phone>" << std::endl
		<< "<gmd:CI_Telephone>" << std::endl
		<< "<gmd:voice>" << std::endl
		<< "<gco:CharacterString>" << metadata->GetContactPhone() << "</gco:CharacterString>" << std::endl
		<< "</gmd:voice>" << std::endl
		<< "</gmd:CI_Telephone>" << std::endl
		<< "</gmd:phone>" << std::endl
		<< "<gmd:address>" << std::endl
		<< "<gmd:CI_Address>" << std::endl
		<< "<gmd:deliveryPoint>" << std::endl
		<< "<gco:CharacterString>" << metadata->GetContactAddress() << "</gco:CharacterString>" << std::endl
		<< "</gmd:deliveryPoint>" << std::endl
		<< "<gmd:electronicMailAddress>" << std::endl
		<< "<gco:CharacterString>" << metadata->GetContactEmail() << "</gco:CharacterString>" << std::endl
		<< "</gmd:electronicMailAddress>" << std::endl
		<< "</gmd:CI_Address>" << std::endl
		<< "</gmd:address>" << std::endl
		<< "</gmd:CI_Contact>" << std::endl
		<< "</gmd:contactInfo>" << std::endl
		<< "</gmd:CI_ResponsibleParty>" << std::endl
		<< "</gmd:contact>" << std::endl;
}

void XMLWriter::WriteXMLDeclaration(std::ostream& output) {
	output << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>" << std::endl;
}

std::string XMLWriter::NSGeo3DML(SchemaVersion v) {
	std::string nsGeo3DMLBase("xmlns:geo3dml=\"http://www.cgs.gov.cn/geo3dml");
	switch (v) {
	case Schema_1_0:
		return nsGeo3DMLBase + "\"";
	case Schema_1_x:
		return nsGeo3DMLBase + "/1.x\"";
	default:
		return nsGeo3DMLBase + "\"";
	}
}

std::string XMLWriter::NSDefault(SchemaVersion v) {
	std::string nsDefaultBase("xmlns=\"http://www.cgs.gov.cn/geo3dml");
	switch (v) {
	case Schema_1_0:
		return nsDefaultBase + "\"";
	case Schema_1_x:
		return nsDefaultBase + "/1.x\"";
	default:
		return nsDefaultBase + "\"";
	}
}

void XMLWriter::OpenXMLFileForOutput(const std::string& xmlFilePath, std::ofstream& xmlFile) {
#if defined(_WIN32)
	wchar_t* wPath = __xmlIOWin32UTF8ToWChar(xmlFilePath.c_str());
	if (wPath != NULL) {
		xmlFile.open(wPath);
		xmlFree(wPath);
	} else {
		xmlFile.open(xmlFilePath);
	}
#else
	xmlFile.open(xmlFilePath);
#endif
	xmlFile.setf(std::ios_base::fixed);
	xmlFile.precision(6);
}