#pragma once

#include <g3dxml/XMLReaderHelper.h>
#include <g3dxml/XMLIO.h>

namespace g3dxml {

	class XMLFeatureClassReader : public XMLIO {
	public:
		/// Name of the feature class elment.
		static std::string Element;

	public:
		/// Constructor.
		/// @param factory the factory of Geo3DML objects. The factory object should be deallocated by the caller.
		XMLFeatureClassReader(geo3dml::ObjectFactory* factory);
		virtual ~XMLFeatureClassReader();

		geo3dml::FeatureClass* ReadFeatureClass(xmlTextReaderPtr reader);

	private:
		bool ReadSchema(xmlTextReaderPtr reader, geo3dml::FeatureClass* f);

	private:
		static std::string Element_Name;
		static std::string Element_Schema;

	private:
		geo3dml::ObjectFactory* g3dFactory_;
	};
}
