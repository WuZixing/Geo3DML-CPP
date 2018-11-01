#pragma once

#include <geo3dml/ObjectFactory.h>
#include <g3dxml/XMLIO.h>

namespace g3dxml {

	class XMLReader : public XMLIO {
	public:
		/// Constructor.
		/// @param factory the factory of Geo3DML objects. The factory object should be deallocated by the caller.
		XMLReader(geo3dml::ObjectFactory* factory);
		virtual ~XMLReader();

		/// Load Geo3DML data from XML file.
		/// The current working directory should be set as the file's direcotry before calling this method.
		geo3dml::Object* LoadXMLFile(const std::string& file);

	private:
		geo3dml::ObjectFactory* g3dFactory_;
	};
}
