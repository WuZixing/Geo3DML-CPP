#pragma once

#include <g3dxml/XMLReaderHelper.h>
#include <g3dxml/XMLIO.h>

namespace g3dxml {

	class XMLGeometryReader : public XMLIO {
	public:
		/// Name of the geometry element.
		static std::string Element;

	public:
		/// Constructor.
		/// @param factory the factory of Geo3DML objects. The factory object should be deallocated by the caller.
		XMLGeometryReader(geo3dml::ObjectFactory* factory);
		virtual ~XMLGeometryReader();

		geo3dml::Geometry* ReadGeometry(xmlTextReaderPtr reader);

	private:
		geo3dml::Geometry* ReadShape(xmlTextReaderPtr reader);
		bool ReadShapeProperty(xmlTextReaderPtr reader, geo3dml::Geometry* toShape);

	private:
		static std::string Element_Shape;
		static std::string Element_ShapeProperty;

	private:
		geo3dml::ObjectFactory * g3dFactory_;
	};
}