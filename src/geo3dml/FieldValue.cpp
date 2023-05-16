#include <geo3dml/FieldValue.h>
#include <geo3dml/Utils.h>

using namespace geo3dml;

bool FieldValue::IsTrue(const std::string& str) {
	return geo3dml::IsTrue(str);
}

FieldValue::FieldValue() {
	value_.vDouble = 0;
	valueType_ = Field::ValueType::Unknown;
}

FieldValue::FieldValue(const std::string& fieldName) : fieldName_(fieldName) {
	value_.vDouble = 0;
	valueType_ = Field::ValueType::Unknown;
}

FieldValue::FieldValue(const std::string& fieldName, bool value) : fieldName_(fieldName) {
	value_.vBool = value;
	valueType_ = Field::ValueType::Boolean;
}

FieldValue::FieldValue(const std::string& fieldName, int value) : fieldName_(fieldName) {
	value_.vInt = value;
	valueType_ = Field::ValueType::Integer;
}

FieldValue::FieldValue(const std::string& fieldName, double value) : fieldName_(fieldName) {
	value_.vDouble = value;
	valueType_ = Field::ValueType::Double;
}

FieldValue::FieldValue(const std::string& fieldName, const std::string& value) : fieldName_(fieldName) {
	strValue_ = value;
	valueType_ = Field::ValueType::Text;
}

FieldValue::~FieldValue() {

}

FieldValue& FieldValue::SetFieldName(const std::string& name) {
	fieldName_ = name;
	return *this;
}

const std::string& FieldValue::FieldName() const {
	return fieldName_;
}

Field::ValueType FieldValue::ValueType() const {
	return valueType_;
}

FieldValue& FieldValue::SetBool(bool v) {
	value_.vBool = v;
	valueType_ = Field::ValueType::Boolean;
	return *this;
}

FieldValue& FieldValue::SetInt(int v) {
	value_.vInt = v;
	valueType_ = Field::ValueType::Integer;
	return *this;
}

FieldValue& FieldValue::SetDouble(double v) {
	value_.vDouble = v;
	valueType_ = Field::ValueType::Double;
	return *this;
}

FieldValue& FieldValue::SetString(const std::string& v) {
	strValue_ = v;
	valueType_ = Field::ValueType::Text;
	return *this;
}

bool FieldValue::IsBool() const {
	return valueType_ == Field::ValueType::Boolean;
}

bool FieldValue::IsInt() const {
	return valueType_ == Field::ValueType::Integer;
}

bool FieldValue::IsDouble() const {
	return valueType_ == Field::ValueType::Double;
}

bool FieldValue::IsString() const {
	return valueType_ == Field::ValueType::Text;
}

bool FieldValue::GetBool() const {
	return value_.vBool;
}

int FieldValue::GetInt() const {
	return value_.vInt;
}

double FieldValue::GetDouble() const {
	return value_.vDouble;
}

std::string FieldValue::GetString() const {
	return strValue_;
}
