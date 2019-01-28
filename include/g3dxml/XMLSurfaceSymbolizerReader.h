#pragma once

#include <g3dxml/XMLReaderHelper.h>
#include <g3dxml/XMLIO.h>

namespace g3dxml {

	class XMLSurfaceSymbolizerReader : public XMLIO {
	public:
		/// Name of the geometry element.
		static std::string Element;

	public:
		/// Constructor.
		/// @param factory the factory of Geo3DML objects. The factory object should be deallocated by the caller.
		XMLSurfaceSymbolizerReader(geo3dml::ObjectFactory* factory);
		virtual ~XMLSurfaceSymbolizerReader();

		geo3dml::SurfaceSymbolizer* ReadSurfaceSym(xmlTextReaderPtr reader);

	private:
		bool ReadFront(xmlTextReaderPtr reader, geo3dml::SurfaceSymbolizer* toSurfaceSym);
		bool ReadBack(xmlTextReaderPtr reader, geo3dml::SurfaceSymbolizer* toSurfaceSym);
		bool ReadVertex(xmlTextReaderPtr reader, geo3dml::SurfaceSymbolizer* toSurfaceSym);
		bool ReadFrame(xmlTextReaderPtr reader, geo3dml::SurfaceSymbolizer* toSurfaceSym);

	private:
		const std::string Element_Front;
		const std::string Element_Back;
		const std::string Element_Vertex;
		const std::string Element_Frame;


	private:
		geo3dml::ObjectFactory* g3dFactory_;
	};
}
