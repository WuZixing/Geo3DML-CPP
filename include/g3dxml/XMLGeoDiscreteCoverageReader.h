// UTF-8编码
#pragma once

#include <g3dxml/XMLReaderHelper.h>
#include <g3dxml/XMLIO.h>

namespace g3dxml {

	class XMLGeoDiscreteCoverageReader : public XMLIO {
	public:
		/// Name of the GeoDiscreteCoverage element.
		static const std::string Element;

	public:
		/// Constructor.
		/// @param factory the factory of Geo3DML objects. The factory object should be deallocated by the caller.
		XMLGeoDiscreteCoverageReader(geo3dml::ObjectFactory* factory);
		virtual ~XMLGeoDiscreteCoverageReader();

		bool ReadGeoDiscreteCoverage(xmlTextReaderPtr reader, geo3dml::Geometry* toShape);
		bool ReadRangeType(xmlTextReaderPtr reader, geo3dml::ShapeProperty* shapeProperty);
		bool ReadRangeSet(xmlTextReaderPtr reader, geo3dml::ShapeProperty* shapeProperty);
		bool ReadRangeSetField(xmlTextReaderPtr reader, geo3dml::ShapeProperty* shapeProperty, int fieldIndex);
		bool ReadFieldValues(xmlTextReaderPtr reader, geo3dml::ShapeProperty* shapeProperty, int fieldIndex);
		/// Read element value of a field of unsupported type.
		bool ReadElementValueAsOther(xmlTextReaderPtr reader, const std::string& elemName);

	private:
		static const std::string Element_RangeType;
		static const std::string Element_RangeSet;

	private:
		geo3dml::ObjectFactory * g3dFactory_;
	};
}
