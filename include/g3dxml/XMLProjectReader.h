#pragma once

#include <g3dxml/XMLReaderHelper.h>
#include <g3dxml/XMLIO.h>

namespace g3dxml {

	class XMLProjectReader : public XMLIO {
	public:
		/// Name of the project elment.
		static std::string Element;

	public:
		/// Constructor.
		/// @param factory the factory of Geo3DML objects. The factory object should be deallocated by the caller.
		/// @param projectDirectory The base directory used to build absolute path for included XML files, which are usually included by relative paths.
		XMLProjectReader(geo3dml::ObjectFactory* factory, const std::string& projectDirectory);
		virtual ~XMLProjectReader();

		geo3dml::Project* ReadProject(xmlTextReaderPtr reader);

	private:
		geo3dml::Model* ReadModel(xmlTextReaderPtr reader);
		geo3dml::Map* ReadMap(xmlTextReaderPtr reader);
		bool ReadStyle(xmlTextReaderPtr reader, geo3dml::Project* project);
		bool ReadLight(xmlTextReaderPtr reader, geo3dml::Light& light);

	private:
		static std::string Element_Name;
		static std::string Element_Description;
		static std::string Element_Model;
		static std::string Element_Include;
		static std::string Element_Style;
		static std::string Element_Light;
		static std::string Element_Map;

	private:
		geo3dml::ObjectFactory* g3dFactory_;
		std::string projectDirectory_;
	};
}