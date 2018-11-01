#pragma once

#include <g3dxml/XMLReaderHelper.h>
#include <g3dxml/XMLIO.h>

namespace g3dxml {

	class XMLModelReader : public XMLIO {
	public:
		/// Name of the model element.
		static std::string Element;
		static bool IsModelElementName(const std::string& name);

	public:
		/// Constructor.
		/// @param factory the factory of Geo3DML objects. The factory object should be deallocated by the caller.
		XMLModelReader(geo3dml::ObjectFactory* factory);
		virtual ~XMLModelReader();

		geo3dml::Model* ReadModel(xmlTextReaderPtr reader);
		geo3dml::Model* LoadFromFile(const std::string& file);

	private:
		static std::string OldElement;
		static std::string Element_Name;
		static std::string Element_Type;

	private:
		geo3dml::ObjectFactory* g3dFactory_;
	};
}