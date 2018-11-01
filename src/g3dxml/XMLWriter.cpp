#include <g3dxml/XMLWriter.h>
#include <g3dxml/XMLFeatureClassWriter.h>

using namespace g3dxml;

XMLWriter::XMLWriter() :
	NS_Geo3DML("xmlns:geo3dml=\"http://www.cgs.gov.cn/geo3dml\""),
	NS_Default("xmlns=\"http://www.cgs.gov.cn/geo3dml\""),
	NS_xi("xmlns:xi=\"http://www.w3.org/2001/XInclude\""),
	NS_xsi("xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\""),
	xsi_SchemaLocation("xsi:schemaLocation=\"http://www.cgs.gov.cn/geo3dml\""),
	NS_gml("xmlns:gml=\"http://www.opengis.net/gml/3.2\""),
	NS_swe("xmlns:swe=\"http://www.opengis.net/swe/2.0\""),
	NS_gco("xmlns:gco=\"http://www.isotc211.org/2005/gco\""),
	NS_gmd("xmlns:gmd=\"http://www.isotc211.org/2005/gmd\""),
	NS_xlink("xmlns:xlink=\"http://www.w3.org/1999/xlink\""),
	NS_gmlcov("xmlns:gmlcov=\"http://www.opengis.net/gmlcov/1.0\"") {

}

XMLWriter::~XMLWriter() {

}

bool XMLWriter::Write(geo3dml::Model* model, std::ostream& output) {
	WriteXMLDeclaration(output);
	output << "<geo3dml:Geo3DModel " << NS_Geo3DML << " " << NS_Default << std::endl
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
			if (!fcWriter.Write(model->GetFeatureClassAt(i), output)) {
				SetStatus(false, fcWriter.Error());
				break;
			}
		}
		output << "</FeatureClasses>" << std::endl;
	}
	output << "</geo3dml:Geo3DModel>" << std::endl;
	return IsOK();
}

bool XMLWriter::Write(geo3dml::Project* project, std::ostream& output) {
	WriteXMLDeclaration(output);
	output << "<geo3dml:Geo3DProject " << NS_Geo3DML << " " << NS_Default << std::endl
		<< NS_xi << std::endl
		<< NS_xsi << std::endl
		<< xsi_SchemaLocation << ">" << std::endl;
	output << "<Name>" << project->GetName() << "</Name>" << std::endl
		<< "<Description>" << project->GetDescription() << "</Description>" << std::endl;
	int modelNumber = project->GetModelCount();
	if (modelNumber > 0) {
		output << "<Models>" << std::endl;

		output << "</Models>" << std::endl;
	}
	output << "</geo3dml:Geo3DProject>" << std::endl;
	return IsOK();
}

void XMLWriter::WriteXMLDeclaration(std::ostream& output) {
	output << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>" << std::endl;
}
