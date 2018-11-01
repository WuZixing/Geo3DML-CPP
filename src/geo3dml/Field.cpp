#include <geo3dml/Field.h>

using namespace geo3dml;

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
