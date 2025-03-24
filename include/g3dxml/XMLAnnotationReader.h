// UTF-8编码
#pragma once

#include <g3dxml/XMLReaderHelper.h>
#include <g3dxml/XMLIO.h>

namespace g3dxml {

	class XMLAnnotationReader : public XMLIO {
	public:
		/// Name of the geometry element.
		static const std::string Element;

	public:
		/// Constructor.
		/// @param factory the factory of Geo3DML objects. The factory object should be deallocated by the caller.
		XMLAnnotationReader(geo3dml::ObjectFactory* factory);
		virtual ~XMLAnnotationReader();

		geo3dml::Annotation* ReadAnnotation(xmlTextReaderPtr reader);

	private:
		bool ReadPos(xmlTextReaderPtr reader, geo3dml::Annotation* annotation);
		bool ReadLabel(xmlTextReaderPtr reader, geo3dml::Annotation* annotation);

	private:
		static const std::string Element_Pos;
		static const std::string Element_Label;

	private:
		geo3dml::ObjectFactory* g3dFactory_;
	};
}
