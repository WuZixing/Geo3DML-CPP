#pragma once

#include <g3dxml/XMLReaderHelper.h>
#include <g3dxml/XMLIO.h>

namespace g3dxml {

	class XMLFeatureTypeStyleReader : public XMLIO {
	public:
		/// Name of the layer element.
		static std::string Element;

	public:
		/// Constructor.
		/// @param factory the factory of Geo3DML objects. The factory object should be deallocated by the caller.
		XMLFeatureTypeStyleReader(geo3dml::ObjectFactory* factory);
		virtual ~XMLFeatureTypeStyleReader();

		geo3dml::FeatureTypeStyle* ReadFeatureTypeStyle(xmlTextReaderPtr reader);

	private:
		geo3dml::ObjectFactory* g3dFactory_;
	};
}
