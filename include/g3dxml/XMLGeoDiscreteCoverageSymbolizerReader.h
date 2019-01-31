#pragma once

#include <g3dxml/XMLReaderHelper.h>
#include <g3dxml/XMLIO.h>

namespace g3dxml {

	class XMLGeoDiscreteCoverageSymbolizerReader : public XMLIO {
	public:
		/// Name of the geometry element.
		static std::string Element;

	public:
		/// Constructor.
		/// @param factory the factory of Geo3DML objects. The factory object should be deallocated by the caller.
		XMLGeoDiscreteCoverageSymbolizerReader(geo3dml::ObjectFactory* factory);
		virtual ~XMLGeoDiscreteCoverageSymbolizerReader();

		geo3dml::GeoDiscreteCoverageSymbolizer* ReadCoverageSym(xmlTextReaderPtr reader);

	private:
		geo3dml::ObjectFactory* g3dFactory_;
	};
}
