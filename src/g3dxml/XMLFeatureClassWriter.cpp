// UTF-8编码
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
			const geo3dml::FieldValue* fv = feature->GetField(fieldNames[f]);
			if (fv == nullptr) {
				continue;
			}
			output << "<Field Name=\"" << fv->FieldName() << "\">" << std::endl;
			std::string elementName = XMLFieldReader::ValueTypeToName(fv->ValueType());
			output << "<swe:" << elementName << ">" << std::endl;
			switch (fv->ValueType()) {
			case geo3dml::Field::Text: {
				output << "<swe:value>" << fv->GetString() << "</swe:value>" << std::endl;
				break;
			}
			case geo3dml::Field::Double: {
				output << "<swe:value>" << fv->GetDouble() << "</swe:value>" << std::endl;
				break;
			}
			case geo3dml::Field::Integer: {
				output << "<swe:value>" << fv->GetInt() << "</swe:value>" << std::endl;
				break;
			}
			case geo3dml::Field::Boolean: {
				output << "<swe:value>" << fv->GetBool() << "</swe:value>" << std::endl;
				break;
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
	geo3dml::Geometry* geometry = feature->GetGeometry();
	if (geometry != nullptr) {
		output << "<Geometry>" << std::endl;
		// Shape
		XMLGeometryWriter geoWriter;
		geoWriter.Write(geometry, output, v);
		// Shape property.
		geo3dml::ShapeProperty* vertexProperty = geometry->GetProperty(geo3dml::ShapeProperty::Vertex);
		if (vertexProperty != NULL) {
			XMLShapePropertyWriter propWriter;
			propWriter.Write(vertexProperty, output, v);
		}
		geo3dml::ShapeProperty* edgeProperty = geometry->GetProperty(geo3dml::ShapeProperty::Edge);
		if (edgeProperty != NULL) {
			XMLShapePropertyWriter propWriter;
			propWriter.Write(edgeProperty, output, v);
		}
		geo3dml::ShapeProperty* faceProperty = geometry->GetProperty(geo3dml::ShapeProperty::Face);
		if (faceProperty != NULL) {
			XMLShapePropertyWriter propWriter;
			propWriter.Write(faceProperty, output, v);
		}
		geo3dml::ShapeProperty* voxelProperty = geometry->GetProperty(geo3dml::ShapeProperty::Voxel);
		if (voxelProperty != NULL) {
			XMLShapePropertyWriter propWriter;
			propWriter.Write(voxelProperty, output, v);
		}
		output << "</Geometry>" << std::endl;
	}
	output << "</GeoFeature>" << std::endl
		<< "</Feature>" << std::endl;
}
