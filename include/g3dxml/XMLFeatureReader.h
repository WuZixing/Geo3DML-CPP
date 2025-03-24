// UTF-8编码
#pragma once

#include <g3dxml/XMLReaderHelper.h>
#include <g3dxml/XMLIO.h>
#include <geo3dml/FieldValue.h>

namespace g3dxml {

	class XMLFeatureReader : public XMLIO {
	public:
		/// Name of the feature element.
		static const std::string Element;

	public:
		/// Constructor.
		/// @param factory the factory of Geo3DML objects. The factory object should be deallocated by the caller.
		XMLFeatureReader(geo3dml::ObjectFactory* factory);
		virtual ~XMLFeatureReader();

		geo3dml::Feature* ReadFeature(xmlTextReaderPtr reader);

	private:
		bool ReadFields(xmlTextReaderPtr reader, geo3dml::Feature* feature);
		bool ReadField(xmlTextReaderPtr reader, geo3dml::Feature* feature);
		bool ReadFieldValue(xmlTextReaderPtr reader, const std::string& elementName, geo3dml::Field::ValueType valueType, geo3dml::FieldValue* value);

	private:
		static const std::string Element_Name;
		static const std::string Element_Fields;

	private:
		geo3dml::ObjectFactory* g3dFactory_;
	};
}
