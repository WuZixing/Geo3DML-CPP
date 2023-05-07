#include <g3dxml/XMLShapePropertyWriter.h>
#include <g3dxml/XMLFieldReader.h>

using namespace g3dxml;

XMLShapePropertyWriter::XMLShapePropertyWriter() {

}

XMLShapePropertyWriter::~XMLShapePropertyWriter() {

}

bool XMLShapePropertyWriter::Write(geo3dml::ShapeProperty* shapeProperty, std::ostream& output, SchemaVersion v) {
	output << "<ShapeProperty>" << std::endl
		<< "<GeoDiscreteCoverage gml:id=\"" << shapeProperty->GetID() << "\">" << std::endl;
	output << "<gml:name>" << shapeProperty->Name() << "</gml:name>" << std::endl;
	// gml:domainSet and geo3dml:DomainSetExt
	output << "<gml:domainSet></gml:domainSet>" << std::endl	// Element <gml:domainSet> is required by gml:AbstractCoverageType.
		<< "<DomainSetExt>" << std::endl
		<< "<SamplingFrame xlink:type=\"simple\" xlink:href=\"#" << shapeProperty->TargetShape() << "\" />" << std::endl
		<< "<SamplingTarget>" << geo3dml::ShapeProperty::SamplingTargetToName(shapeProperty->TargetComponent()) << "</SamplingTarget>" << std::endl
		<< "</DomainSetExt>" << std::endl;
	// gmlcov:rangeType which is required by gmlcov:AbstractCoverageType.
	output << "<gmlcov:rangeType>" << std::endl
		<< "<swe:DataRecord>" << std::endl;
	int fieldNumber = shapeProperty->GetFieldCount();
	for (int i = 0; i < fieldNumber; ++i) {
		const geo3dml::Field& field = shapeProperty->GetFieldAt(i);
		XMLFieldReader::WriteField(field, output);
	}
	output << "</swe:DataRecord>" << std::endl
		<< "</gmlcov:rangeType>" << std::endl;
	// gml:rangeSet
	output << "<gml:rangeSet>" << std::endl;
	for (int i = 0; i < fieldNumber; ++i) {
		const geo3dml::Field& field = shapeProperty->GetFieldAt(i);
		switch (field.DataType()) {
		case geo3dml::Field::Boolean:
			WriteBooleanFieldValues(shapeProperty, i, output);
			break;
		case geo3dml::Field::Double:
			WriteDoubleFieldValues(shapeProperty, i, output);
			break;
		case geo3dml::Field::Integer:
			WriteIntFieldValues(shapeProperty, i, output);
			break;
		case geo3dml::Field::Text:
			WriteTextFieldValues(shapeProperty, i, output);
			break;
		default:
			break;
		}
	}
	output << "</gml:rangeSet>" << std::endl;
	output << "</GeoDiscreteCoverage>" << std::endl
		<< "</ShapeProperty>" << std::endl;
	return IsOK();
}

void XMLShapePropertyWriter::WriteDoubleFieldValues(geo3dml::ShapeProperty* shapeProperty, int fieldIndex, std::ostream& output) {
	output << "<gml:ValueArray gml:id=\"\">" << std::endl
		<< "<gml:valueComponents>" << std::endl;
	int valueNumber = shapeProperty->GetValueCount(fieldIndex);
	for (int i = 0; i < valueNumber; ++i) {
		output << "<gml:Quantity>" << shapeProperty->DoubleValue(fieldIndex, i) << "</gml:Quantity>" << std::endl;
	}
	output << "</gml:valueComponents>" << std::endl
		<< "</gml:ValueArray>" << std::endl;
}

void XMLShapePropertyWriter::WriteIntFieldValues(geo3dml::ShapeProperty* shapeProperty, int fieldIndex, std::ostream& output) {
	output << "<gml:ValueArray gml:id=\"\">" << std::endl
		<< "<gml:valueComponents>" << std::endl;
	int valueNumber = shapeProperty->GetValueCount(fieldIndex);
	for (int i = 0; i < valueNumber; ++i) {
		output << "<gml:Count>" << shapeProperty->IntValue(fieldIndex, i) << "</gml:Count>" << std::endl;
	}
	output << "</gml:valueComponents>" << std::endl
		<< "</gml:ValueArray>" << std::endl;
}

void XMLShapePropertyWriter::WriteTextFieldValues(geo3dml::ShapeProperty* shapeProperty, int fieldIndex, std::ostream& output) {
	output << "<gml:ValueArray gml:id=\"\">" << std::endl
		<< "<gml:valueComponents>" << std::endl;
	int valueNumber = shapeProperty->GetValueCount(fieldIndex);
	for (int i = 0; i < valueNumber; ++i) {
		// gml 本身没有一般的 Text 数据类型，所以使用 swe:Text 对象。
		output << "<swe:Text>" << shapeProperty->TextValue(fieldIndex, i) << "</swe:Text>" << std::endl;
	}
	output << "</gml:valueComponents>" << std::endl
		<< "</gml:ValueArray>" << std::endl;
}

void XMLShapePropertyWriter::WriteBooleanFieldValues(geo3dml::ShapeProperty* shapeProperty, int fieldIndex, std::ostream& output) {
	output << "<gml:ValueArray gml:id=\"\">" << std::endl
		<< "<gml:valueComponents>" << std::endl;
	int valueNumber = shapeProperty->GetValueCount(fieldIndex);
	for (int i = 0; i < valueNumber; ++i) {
		output << "<gml:Boolean>" << shapeProperty->BooleanValue(fieldIndex, i) << "</gml:Boolean>" << std::endl;
	}
	output << "</gml:valueComponents>" << std::endl
		<< "</gml:ValueArray>" << std::endl;
}
