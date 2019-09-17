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
	char pathSeperator = '\\';
#else
	char pathSeperator = '/';
#endif
	size_t pos = xmlFilePath.find_last_of(pathSeperator);
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
	output << "<Metadata>" << std::endl
		<< "<Description>" << model->GetDescription() << "</Description>" << std::endl
		<< "<Version>" << model->GetVersion() << "</Version>" << std::endl
		<< "<ToolName>" << model->GetToolName() << "</ToolName>" << std::endl
		<< "<ToolVersion>" << model->GetToolVersion() << "</ToolVersion>" << std::endl
		<< "</Metadata>" << std::endl;
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
	output << "<Name>" << project->GetName() << "</Name>" << std::endl
		<< "<Description>" << project->GetDescription() << "</Description>" << std::endl;
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