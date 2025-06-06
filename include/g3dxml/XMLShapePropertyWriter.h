// UTF-8编码
#pragma once

#include <geo3dml/ShapeProperty.h>
#include <iostream>
#include <g3dxml/XMLIO.h>

namespace g3dxml {

	class XMLShapePropertyWriter : public XMLIO {
	public:
		XMLShapePropertyWriter();
		virtual ~XMLShapePropertyWriter();

		bool Write(geo3dml::ShapeProperty* shapeProperty, std::ostream& output, SchemaVersion v) const;

	private:
		void WriteDoubleFieldValues(geo3dml::ShapeProperty* shapeProperty, int fieldIndex, std::ostream& output) const;
		void WriteIntFieldValues(geo3dml::ShapeProperty* shapeProperty, int fieldIndex, std::ostream& output) const;
		void WriteTextFieldValues(geo3dml::ShapeProperty* shapeProperty, int fieldIndex, std::ostream& output) const;
		void WriteCategoryFieldValues(geo3dml::ShapeProperty* shapeProperty, int fieldIndex, std::ostream& output) const;
		void WriteBooleanFieldValues(geo3dml::ShapeProperty* shapeProperty, int fieldIndex, std::ostream& output) const;
	};
}
