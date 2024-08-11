#pragma once

#include <g3dxml/XMLReaderHelper.h>
#include <g3dxml/XMLIO.h>

namespace g3dxml {

	class XMLStyleReader : public XMLIO {
	public:
		/// Name of the layer element.
		static const std::string Element;

	public:
		/// Constructor.
		/// @param factory the factory of Geo3DML objects. The factory object should be deallocated by the caller.
		XMLStyleReader(geo3dml::ObjectFactory* factory);
		virtual ~XMLStyleReader();

		geo3dml::Style* ReadStyle(xmlTextReaderPtr reader);

	private:
		static const std::string Element_Name;

	private:
		geo3dml::ObjectFactory* g3dFactory_;
	};
}
