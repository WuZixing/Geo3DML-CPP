#include <geo3dml/FieldValue.h>
#include <geo3dml/Utils.h>

using namespace geo3dml;

FieldValue::FieldValue(const std::string& fieldName) {
	fieldName_ = fieldName;
}

FieldValue::~FieldValue() {

}

const std::string& FieldValue::FieldName() const {
	return fieldName_;
}

TextFieldValue::TextFieldValue(const std::string& fieldName) : FieldValue(fieldName) {

}

TextFieldValue::TextFieldValue(const TextFieldValue& v) : FieldValue(v.FieldName()) {
	value_ = v.value_;
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

DoubleFieldValue::DoubleFieldValue(const std::string& fieldName) : FieldValue(fieldName) {

}

DoubleFieldValue::DoubleFieldValue(const DoubleFieldValue& v) : FieldValue(v.FieldName()) {
	value_ = v.value_;
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

IntegerFieldValue::IntegerFieldValue(const std::string& fieldName) : FieldValue(fieldName) {

}

IntegerFieldValue::IntegerFieldValue(const IntegerFieldValue& v) : FieldValue(v.FieldName()) {
	value_ = v.value_;
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

bool BooleanFieldValue::IsTrue(const std::string& str) {
	return geo3dml::IsTrue(str);
}

BooleanFieldValue::BooleanFieldValue(const std::string& fieldName) : FieldValue(fieldName) {

}

BooleanFieldValue::BooleanFieldValue(const BooleanFieldValue& v) : FieldValue(v.FieldName()) {
	value_ = v.value_;
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
