#include <geo3dml/Field.h>
#include <geo3dml/Utils.h>

using namespace geo3dml;

std::string Field::ValueTypeToName(ValueType t) {
	switch (t) {
	case geo3dml::Field::ValueType::Text:
		return "Text";
	case geo3dml::Field::ValueType::Integer:
		return "Integer";
	case geo3dml::Field::ValueType::Double:
		return "Double";
	case geo3dml::Field::ValueType::Boolean:
		return "Boolean";
	case geo3dml::Field::ValueType::Object:
		return "Object";
	default:
		return "Unknown";
	}
}

Field::ValueType Field::NameToValueType(const std::string& name) {
	if (geo3dml::IsiEqual(name, "Text")) {
		return geo3dml::Field::Text;
	} else if (geo3dml::IsiEqual(name, "Double")) {
		return geo3dml::Field::Double;
	} else if (geo3dml::IsiEqual(name, "Integer")) {
		return geo3dml::Field::Integer;
	} else if (geo3dml::IsiEqual(name, "Boolean")) {
		return geo3dml::Field::Boolean;
	} else if (geo3dml::IsiEqual(name, "Object")) {
		return geo3dml::Field::Object;
	} else {
		return geo3dml::Field::Unknown;
	}
}

Field::Field() {
	valueType_ = Unknown;
}

Field::Field(const Field& f) {
	name_ = f.name_;
	label_ = f.label_;
	valueType_ = f.valueType_;
	definition_ = f.definition_;
	description_ = f.description_;
	uom_ = f.uom_;
}

Field::~Field() {

}

Field& Field::Name(const std::string& s) {
	name_ = s;
	return *this;
}

std::string Field::Name() const {
	return name_;
}

Field& Field::Label(const std::string& s) {
	label_ = s;
	return *this;
}

std::string Field::Label() const {
	return label_;
}

Field& Field::DataType(Field::ValueType t) {
	valueType_ = t;
	return *this;
}

Field::ValueType Field::DataType() const {
	return valueType_;
}

Field& Field::Uom(const std::string& s) {
	uom_ = s;
	return *this;
}

std::string Field::Uom() const {
	return uom_;
}

Field& Field::Definition(const std::string& s) {
	definition_ = s;
	return *this;
}

std::string Field::Definition() const {
	return definition_;
}

Field& Field::Description(const std::string& s) {
	description_ = s;
	return *this;
}

std::string Field::Description() const {
	return description_;
}
