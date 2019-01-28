#pragma once

#include <g3dxml/XMLReaderHelper.h>
#include <g3dxml/XMLIO.h>

namespace g3dxml {

	class XMLLineSymbolizerReader : public XMLIO {
	public:
		/// Name of the geometry element.
		static std::string Element;

	public:
		/// Constructor.
		/// @param factory the factory of Geo3DML objects. The factory object should be deallocated by the caller.
		XMLLineSymbolizerReader(geo3dml::ObjectFactory* factory);
		virtual ~XMLLineSymbolizerReader();

		geo3dml::LineSymbolizer* ReadLineSym(xmlTextReaderPtr reader);

	private:
		bool ReadStroke(xmlTextReaderPtr reader, geo3dml::LineSymbolizer* toLineSym);

	private:
		const std::string Element_Stroke;

	private:
		geo3dml::ObjectFactory* g3dFactory_;
	};
}
