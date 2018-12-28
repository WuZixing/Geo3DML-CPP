#pragma once

#include <geo3dml/ShapeProperty.h>
#include <iostream>
#include <g3dxml/XMLIO.h>

namespace g3dxml {

	class XMLShapePropertyWriter : public XMLIO {
	public:
		XMLShapePropertyWriter();
		virtual ~XMLShapePropertyWriter();

		bool Write(geo3dml::ShapeProperty* shapeProperty, std::ostream& output, SchemaVersion v);

	private:
		void WriteDoubleFieldValues(geo3dml::ShapeProperty* shapeProperty, int fieldIndex, std::ostream& output);
		void WriteIntFieldValues(geo3dml::ShapeProperty* shapeProperty, int fieldIndex, std::ostream& output);
		void WriteTextFieldValues(geo3dml::ShapeProperty* shapeProperty, int fieldIndex, std::ostream& output);
		void WriteBooleanFieldValues(geo3dml::ShapeProperty* shapeProperty, int fieldIndex, std::ostream& output);
	};
}
