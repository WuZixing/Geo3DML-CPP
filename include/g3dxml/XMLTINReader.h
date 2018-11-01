#pragma once

#include <g3dxml/XMLReaderHelper.h>
#include <g3dxml/XMLIO.h>

namespace g3dxml {

	class XMLTINReader : public XMLIO {
	public:
		/// Name of the geometry element.
		static std::string Element;

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
		static std::string Element_Vertex;
		static std::string Element_Triangle;
		static std::string Element_VertexList;
		static std::string Element_NeighborList;

	private:
		geo3dml::ObjectFactory* g3dFactory_;
	};
}
