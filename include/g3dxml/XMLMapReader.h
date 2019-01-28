#pragma once

#include <g3dxml/XMLReaderHelper.h>
#include <g3dxml/XMLIO.h>

namespace g3dxml {

	class XMLMapReader : public XMLIO {
	public:
		/// Name of the map element.
		static std::string Element;

	public:
		/// Constructor.
		/// @param factory the factory of Geo3DML objects. The factory object should be deallocated by the caller.
		XMLMapReader(geo3dml::ObjectFactory* factory);
		virtual ~XMLMapReader();

		geo3dml::Map* ReadMap(xmlTextReaderPtr reader);
		geo3dml::Map* LoadFromFile(const std::string& file);

	private:
		static std::string Element_Name;
		static std::string Element_Description;

	private:
		geo3dml::ObjectFactory* g3dFactory_;
	};
}
