// UTF-8编码
#pragma once

#include <geo3dml/Project.h>
#include <g3dxml/XMLIO.h>
#include <fstream>

namespace g3dxml {

	class XMLWriter : public XMLIO {
	public:
		XMLWriter();
		virtual ~XMLWriter();

		bool Write(geo3dml::Project* project, const std::string& xmlFilePath, SchemaVersion v);
		bool Write(geo3dml::Model* model, const std::string& xmlFilePath, SchemaVersion v);
		bool Write(geo3dml::Map* map, const std::string& xmlFilePath, SchemaVersion v);

	private:
		bool Write(geo3dml::Project* project, std::ostream& output, SchemaVersion v);
		bool Write(geo3dml::Model* model, std::ostream& output, SchemaVersion v);
		bool Write(geo3dml::Map* map, std::ostream& output, SchemaVersion v);
		void WriteContactOfMetadata(const geo3dml::AbstractMetadata* metadata, std::ostream& output);
		void WriteXMLDeclaration(std::ostream& output);
		std::string RawNameSpaceBase(SchemaVersion v) const;
		std::string NSGeo3DML(SchemaVersion v) const;
		std::string NSDefault(SchemaVersion v) const;
		std::string SchemaLocation(SchemaVersion v) const;

		void OpenXMLFileForOutput(const std::string& xmlFilePath, std::ofstream& xmlFile);

	private:
		const std::string NS_xi;
		const std::string NS_xsi;
		const std::string NS_gml;
		const std::string NS_swe;
		const std::string NS_gco;
		const std::string NS_gmd;
		const std::string NS_xlink;
		const std::string NS_gmlcov;
		const std::string NS_ogc;
		const std::string NS_se;

	private:
		std::string projectDirectory_;
	};
}
