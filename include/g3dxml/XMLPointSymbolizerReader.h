#pragma once

#include <g3dxml/XMLReaderHelper.h>
#include <g3dxml/XMLIO.h>

namespace g3dxml {

	class XMLPointSymbolizerReader : public XMLIO {
	public:
		/// Name of the geometry element.
		static std::string Element;

	public:
		/// Constructor.
		/// @param factory the factory of Geo3DML objects. The factory object should be deallocated by the caller.
		XMLPointSymbolizerReader(geo3dml::ObjectFactory* factory);
		virtual ~XMLPointSymbolizerReader();

		geo3dml::PointSymbolizer* ReadPointSym(xmlTextReaderPtr reader);

	private:
		bool ReadGraphic(xmlTextReaderPtr reader, geo3dml::PointSymbolizer* toPointSym);

	private:
		const std::string Element_Graphic;

	private:
		geo3dml::ObjectFactory* g3dFactory_;
	};
}
