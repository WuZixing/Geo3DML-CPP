#pragma once

#include <geo3dml/Project.h>
#include <iostream>
#include <g3dxml/XMLIO.h>

namespace g3dxml {

	class XMLWriter : public XMLIO {
	public:
		XMLWriter();
		virtual ~XMLWriter();

		bool Write(geo3dml::Model* model, std::ostream& output);
		bool Write(geo3dml::Project* project, std::ostream& output);

	private:
		void WriteXMLDeclaration(std::ostream& output);

	private:
		const std::string NS_Geo3DML;
		const std::string NS_Default;
		const std::string NS_xi;
		const std::string NS_xsi;
		const std::string xsi_SchemaLocation;
		const std::string NS_gml;
		const std::string NS_swe;
		const std::string NS_gco;
		const std::string NS_gmd;
		const std::string NS_xlink;
		const std::string NS_gmlcov;
	};
}
