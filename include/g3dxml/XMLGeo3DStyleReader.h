#pragma once

#include <g3dxml/XMLReaderHelper.h>
#include <g3dxml/XMLIO.h>

namespace g3dxml {

	class XMLGeo3DStyleReader : public XMLIO {
	public:
		/// Name of the layer element.
		static std::string Element;

	public:
		/// Constructor.
		/// @param factory the factory of Geo3DML objects. The factory object should be deallocated by the caller.
		XMLGeo3DStyleReader(geo3dml::ObjectFactory* factory);
		virtual ~XMLGeo3DStyleReader();

		geo3dml::Geo3DStyle* ReadStyle(xmlTextReaderPtr reader);

	private:
		static std::string Element_Name;

	private:
		geo3dml::ObjectFactory* g3dFactory_;
	};
}
