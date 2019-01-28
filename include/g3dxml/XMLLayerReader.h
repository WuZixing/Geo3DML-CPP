#pragma once

#include <g3dxml/XMLReaderHelper.h>
#include <g3dxml/XMLIO.h>

namespace g3dxml {

	class XMLLayerReader : public XMLIO {
	public:
		/// Name of the layer element.
		static std::string Element;

	public:
		/// Constructor.
		/// @param factory the factory of Geo3DML objects. The factory object should be deallocated by the caller.
		XMLLayerReader(geo3dml::ObjectFactory* factory);
		virtual ~XMLLayerReader();

		geo3dml::Layer* ReadLayer(xmlTextReaderPtr reader);

	private:
		static std::string Element_Name;
		static std::string Element_FeatureClass;

	private:
		geo3dml::ObjectFactory* g3dFactory_;
	};
}
