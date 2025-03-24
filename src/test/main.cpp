// UTF-8编码

#include <filesystem>
#include <iostream>
#include <g3dvtk/ObjectFactory.h>
#include <g3dxml/XMLReader.h>
#include <g3dxml/XMLWriter.h>

int main() {
	const std::filesystem::path dataFilePath("D:\\Workspace\\Geo3DML\\examples\\data\\project.xml");
	const std::filesystem::path outputDir("D:\\Temp\\Geo3DML");
	// 基于VTK工厂类读写Geo3DML文件。
	//*
	{
		std::cout << "load Geo3DML from file with g3dvtk::ObjectFactory..." << std::endl;
		g3dvtk::ObjectFactory g3dVtkFactory;
		g3dxml::XMLReader xmlReader(&g3dVtkFactory);
		geo3dml::Object* g3dObject = xmlReader.LoadXMLFile(dataFilePath.string());
		if (g3dObject == nullptr) {
            std::cerr << "failed to load Geo3DML from XML file with g3dvtk::ObjectFactory." << std::endl;
		} else {
			std::cout << "write to Geo3DML file..." << std::endl;
			g3dxml::XMLWriter xmlWriter;
			geo3dml::Model* model = dynamic_cast<geo3dml::Model*>(g3dObject);
			if (model != nullptr) {
				std::filesystem::path out1 = outputDir / "v1" / "g3dvtk" / "model.xml";
				xmlWriter.Write(model, out1.string(), g3dxml::Schema_1_0);
				std::filesystem::path out2 = outputDir / "v2" / "g3dvtk" / "model.xml";
				xmlWriter.Write(model, out2.string(), g3dxml::Schema_2_0);
			} else {
				geo3dml::Project* project = dynamic_cast<geo3dml::Project*>(g3dObject);
				if (project != nullptr) {
					std::filesystem::path out1 = outputDir / "v1" / "g3dvtk" / "project.xml";
					xmlWriter.Write(project, out1.string(), g3dxml::Schema_1_0);
					std::filesystem::path out2 = outputDir / "v2" / "g3dvtk" / "project.xml";
					xmlWriter.Write(project, out2.string(), g3dxml::Schema_2_0);
				}
			}
			delete g3dObject;
		}
	}
	//*/
	// 基于缺省工厂类读写Geo3DML文件。
	{
		std::cout << "load Geo3DML from file with geo3dml::DefaultObjectFactory..." << std::endl;
		g3dxml::XMLReader xmlReader;
		geo3dml::Object* g3dObject = xmlReader.LoadXMLFile(dataFilePath.string());
		if (g3dObject == nullptr) {
			std::cerr << "failed to load Geo3DML from XML file with geo3dml::DefaultObjectFactory." << std::endl;
		} else {
			std::cout << "write to Geo3DML file..." << std::endl;
			g3dxml::XMLWriter xmlWriter;
			geo3dml::Model* model = dynamic_cast<geo3dml::Model*>(g3dObject);
			if (model != nullptr) {
				std::filesystem::path out1 = outputDir / "v1" / "default" / "model.xml";
				xmlWriter.Write(model, out1.string(), g3dxml::Schema_1_0);
				std::filesystem::path out2 = outputDir / "v2" / "default" / "model.xml";
				xmlWriter.Write(model, out2.string(), g3dxml::Schema_2_0);
			} else {
				geo3dml::Project* project = dynamic_cast<geo3dml::Project*>(g3dObject);
				if (project != nullptr) {
					std::filesystem::path out1 = outputDir / "v1" / "default" / "project.xml";
					xmlWriter.Write(project, out1.string(), g3dxml::Schema_1_0);
					std::filesystem::path out2 = outputDir / "v2" / "default" / "project.xml";
					xmlWriter.Write(project, out2.string(), g3dxml::Schema_2_0);
				}
			}
			delete g3dObject;
		}
	}
}
