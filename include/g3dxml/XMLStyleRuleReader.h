#pragma once

#include <g3dxml/XMLReaderHelper.h>
#include <g3dxml/XMLIO.h>

namespace g3dxml {

	class XMLStyleRuleReader : public XMLIO {
	public:
		/// Name of the layer element.
		static std::string Element;

	public:
		/// Constructor.
		/// @param factory the factory of Geo3DML objects. The factory object should be deallocated by the caller.
		XMLStyleRuleReader(geo3dml::ObjectFactory* factory);
		virtual ~XMLStyleRuleReader();

		geo3dml::StyleRule* ReadStyleRule(xmlTextReaderPtr reader);

	private:
		geo3dml::StyleRule* ReadFilter(xmlTextReaderPtr reader);
		geo3dml::StyleRule* ReadEqualToFilter(xmlTextReaderPtr reader);

	private:
		const std::string Element_Filter;
		const std::string Element_Filter_IsEqualTo;

	private:
		geo3dml::ObjectFactory* g3dFactory_;
	};
}
