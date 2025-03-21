// UTF-8编码
#pragma once

#include <g3dxml/XMLReaderHelper.h>
#include <g3dxml/XMLIO.h>

namespace g3dxml {

	class XMLTINReader : public XMLIO {
	public:
		/// Name of the geometry element.
		static const std::string Element;

	public:
		/// Constructor.
		/// @param factory the factory of Geo3DML objects. The factory object should be deallocated by the caller.
		XMLTINReader(geo3dml::ObjectFactory* factory);
		virtual ~XMLTINReader();

		geo3dml::TIN* ReadTIN(xmlTextReaderPtr reader);

	private:
		bool ReadVertex(xmlTextReaderPtr reader, geo3dml::TIN* tin);
		bool ReadTriangle(xmlTextReaderPtr reader, geo3dml::TIN* tin);

	private:
		static const std::string Element_Vertex;
		static const std::string Element_Triangle;
		static const std::string Element_VertexList;
		static const std::string Element_NeighborList;

	private:
		geo3dml::ObjectFactory* g3dFactory_;
	};
}
