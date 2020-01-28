#pragma once

#include <geo3dml/Field.h>
#include <g3dxml/XMLReaderHelper.h>
#include <g3dxml/XMLIO.h>
#include <ostream>

namespace g3dxml {

	class XMLFieldReader : public XMLIO {
	public:
		/// Name of the field element.
		static std::string Element;

		static geo3dml::Field::ValueType NameToValueType(const std::string& n);
		static std::string ValueTypeToName(geo3dml::Field::ValueType t);

	public:
		static void WriteField(const geo3dml::Field& field, std::ostream& output);

	public:
		bool ReadField(xmlTextReaderPtr reader, geo3dml::Field* field);

	private:
		bool ReadFieldDefinition(xmlTextReaderPtr reader, const std::string& fieldElementName, geo3dml::Field* field);
	};
}
