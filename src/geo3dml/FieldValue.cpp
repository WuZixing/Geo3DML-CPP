#include <geo3dml/FieldValue.h>

using namespace geo3dml;

FieldValue::FieldValue(const std::string& name) {
	fieldName_ = name;
}

FieldValue::~FieldValue() {

}

const std::string& FieldValue::Name() const {
	return fieldName_;
}

TextFieldValue::TextFieldValue(const std::string& name) : FieldValue(name) {

}

TextFieldValue::~TextFieldValue() {

}

Field::ValueType TextFieldValue::ValueType() const {
	return Field::Text;
}

TextFieldValue& TextFieldValue::Value(const std::string& v) {
	value_ = v;
	return *this;
}

const std::string& TextFieldValue::Value() const {
	return value_;
}

DoubleFieldValue::DoubleFieldValue(const std::string& name) : FieldValue(name) {

}

DoubleFieldValue::~DoubleFieldValue() {

}

Field::ValueType DoubleFieldValue::ValueType() const {
	return Field::Double;
}

DoubleFieldValue& DoubleFieldValue::Value(double v) {
	value_ = v;
	return *this;
}

double DoubleFieldValue::Value() const {
	return value_;
}

IntegerFieldValue::IntegerFieldValue(const std::string& name) : FieldValue(name) {

}

IntegerFieldValue::~IntegerFieldValue() {

}

Field::ValueType IntegerFieldValue::ValueType() const {
	return Field::Integer;
}

IntegerFieldValue& IntegerFieldValue::Value(int v) {
	value_ = v;
	return *this;
}

int IntegerFieldValue::Value() const {
	return value_;
}

BooleanFieldValue::BooleanFieldValue(const std::string& name) : FieldValue(name) {

}

BooleanFieldValue::~BooleanFieldValue() {

}

Field::ValueType BooleanFieldValue::ValueType() const {
	return Field::Boolean;
}

BooleanFieldValue& BooleanFieldValue::Value(bool v) {
	value_ = v;
	return *this;
}

bool BooleanFieldValue::Value() const {
	return value_;
}
