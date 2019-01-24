#include <g3dxml/XMLFeatureClassWriter.h>
#include <g3dxml/XMLFieldReader.h>
#include <g3dxml/XMLGeometryWriter.h>
#include <g3dxml/XMLShapePropertyWriter.h>

using namespace g3dxml;

XMLFeatureClassWriter::XMLFeatureClassWriter() {

}

XMLFeatureClassWriter::~XMLFeatureClassWriter() {

}

bool XMLFeatureClassWriter::Write(geo3dml::FeatureClass* fc, std::ostream& output, SchemaVersion v) {
	output << "<FeatureClass>" << std::endl
		<< "<GeoFeatureClass gml:id=\"" << fc->GetID() << "\">" << std::endl;
	output << "<gml:name>" << fc->GetName() << "</gml:name>" << std::endl;
	WriteSchema(fc, output);
	WriteFeatures(fc, output, v);
	output << "</GeoFeatureClass>" << std::endl
		<< "</FeatureClass>" << std::endl;
	return IsOK();
}

void XMLFeatureClassWriter::WriteSchema(geo3dml::FeatureClass* fc, std::ostream& output) {
	int fieldNumber = fc->GetFieldCount();
	if (fieldNumber < 1) {
		return;
	}
	output << "<Schema>" << std::endl;
	for (int i = 0; i < fieldNumber; ++i) {
		const geo3dml::Field& field = fc->GetFieldAt(i);
		XMLFieldReader::WriteField(field, output);
	}
	output << "</Schema>" << std::endl;
}

void XMLFeatureClassWriter::WriteFeatures(geo3dml::FeatureClass* fc, std::ostream& output, SchemaVersion v) {
	int featureNumber = fc->GetFeatureCount();
	if (featureNumber < 1) {
		return;
	}
	output << "<Features>" << std::endl;
	for (int i = 0; i < featureNumber; ++i) {
		geo3dml::Feature* feature = fc->GetFeatureAt(i);
		WriteFeature(feature, output, v);
	}
	output << "</Features>" << std::endl;
}

void XMLFeatureClassWriter::WriteFeature(geo3dml::Feature* feature, std::ostream& output, SchemaVersion v) {
	output << "<Feature>" << std::endl
		<< "<GeoFeature gml:id=\"" << feature->GetID() << "\">" << std::endl;
	output << "<gml:name>" << feature->GetName() << "</gml:name>" << std::endl;
	// Fields
	std::vector<std::string> fieldNames = feature->GetFieldNames();
	size_t fieldNumber = fieldNames.size();
	if (fieldNumber > 0) {
		output << "<Fields>" << std::endl;
		for (size_t f = 0; f < fieldNumber; ++f) {
			geo3dml::FieldValue* fv = feature->GetField(fieldNames[f]);
			if (fv == NULL) {
				continue;
			}
			output << "<Field Name=\"" << fv->Name() << "\">" << std::endl;
			std::string elementName = XMLFieldReader::ValueTypeToName(fv->ValueType());
			output << "<swe:" << elementName << ">" << std::endl;
			switch (fv->ValueType()) {
			case geo3dml::Field::Text: {
				geo3dml::TextFieldValue* textValue = dynamic_cast<geo3dml::TextFieldValue*>(fv);
				if (textValue != NULL) {
					output << "<swe:value>" << textValue->Value() << "</swe:value>" << std::endl;
				}
				break;
			}
			case geo3dml::Field::Double: {
				geo3dml::DoubleFieldValue* doubleValue = dynamic_cast<geo3dml::DoubleFieldValue*>(fv);
				if (doubleValue != NULL) {
					output << "<swe:value>" << doubleValue->Value() << "</swe:value>" << std::endl;
				}
				break;
			}
			case geo3dml::Field::Integer: {
				geo3dml::IntegerFieldValue* intValue = dynamic_cast<geo3dml::IntegerFieldValue*>(fv);
				if (intValue != NULL) {
					output << "<swe:value>" << intValue->Value() << "</swe:value>" << std::endl;
				}
				break;
			}
			case geo3dml::Field::Boolean: {
				geo3dml::BooleanFieldValue* boolValue = dynamic_cast<geo3dml::BooleanFieldValue*>(fv);
				if (boolValue != NULL) {
					output << "<swe:value>" << boolValue->Value() << "</swe:value>" << std::endl;
				}
			}
			default:
				break;
			}
			output << "</swe:" << elementName << ">" << std::endl;
			output << "</Field>" << std::endl;
		}
		output << "</Fields>" << std::endl;
	}
	// Geometries
	int geometryNumber = feature->GetGeometryCount();
	if (geometryNumber > 0) {
		if (v == Schema_1_0) {
			geometryNumber = 1;
		} else {
			output << "<Geometries>" << std::endl;
		}
		for (int i = 0; i < geometryNumber; ++i) {
			geo3dml::Geometry* geometry = feature->GetGeometryAt(i);
			if (v == Schema_1_0) {
				output << "<Geometry>" << std::endl;
			} else {
				output << "<Geometry Name=\"" << geometry->GetName() << "\" LOD=\"" << geometry->GetLODLevel() << "\">" << std::endl;
			}
			// Shape
			XMLGeometryWriter geoWriter;
			if (!geoWriter.Write(geometry, output, v)) {
				SetStatus(false, geoWriter.Error());
				break;
			}
			// Shape property.
			geo3dml::ShapeProperty* vertexProperty = geometry->GetProperty(geo3dml::ShapeProperty::Vertex);
			if (vertexProperty != NULL) {
				XMLShapePropertyWriter propWriter;
				if (!propWriter.Write(vertexProperty, output, v)) {
					SetStatus(false, propWriter.Error());
					break;
				}
			}
			geo3dml::ShapeProperty* edgeProperty = geometry->GetProperty(geo3dml::ShapeProperty::Edge);
			if (edgeProperty != NULL) {
				XMLShapePropertyWriter propWriter;
				if (!propWriter.Write(edgeProperty, output, v)) {
					SetStatus(false, propWriter.Error());
					break;
				}
			}
			geo3dml::ShapeProperty* faceProperty = geometry->GetProperty(geo3dml::ShapeProperty::Face);
			if (faceProperty != NULL) {
				XMLShapePropertyWriter propWriter;
				if (!propWriter.Write(faceProperty, output, v)) {
					SetStatus(false, propWriter.Error());
					break;
				}
			}
			geo3dml::ShapeProperty* voxelProperty = geometry->GetProperty(geo3dml::ShapeProperty::Voxel);
			if (voxelProperty != NULL) {
				XMLShapePropertyWriter propWriter;
				if (!propWriter.Write(voxelProperty, output, v)) {
					SetStatus(false, propWriter.Error());
					break;
				}
			}
			output << "</Geometry>" << std::endl;
		}
		if (v != Schema_1_0) {
			output << "</Geometries>" << std::endl;
		}
	}
	output << "</GeoFeature>" << std::endl
		<< "</Feature>" << std::endl;
}
