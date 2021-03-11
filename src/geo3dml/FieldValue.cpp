#include <geo3dml/FieldValue.h>
#include <geo3dml/Utils.h>

using namespace geo3dml;

bool FieldValue::IsTrue(const std::string& str) {
	return geo3dml::IsTrue(str);
}

FieldValue::FieldValue() {

}

FieldValue::FieldValue(const std::string& fieldName) : fieldName_(fieldName) {

}

FieldValue::FieldValue(const std::string& fieldName, bool value) : fieldName_(fieldName), value_(value) {

}

FieldValue::FieldValue(const std::string& fieldName, int value) : fieldName_(fieldName), value_(value) {

}

FieldValue::FieldValue(const std::string& fieldName, double value) : fieldName_(fieldName), value_(value) {

}

FieldValue::FieldValue(const std::string& fieldName, const std::string& value) : fieldName_(fieldName), value_(value) {

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
	switch (value_.index()) {
	case 1:
		return Field::ValueType::Boolean;
	case 2:
		return Field::ValueType::Integer;
	case 3:
		return Field::ValueType::Double;
	case 4:
		return Field::ValueType::Text;
	default:
		return Field::ValueType::Unknown;
	}
}

FieldValue* FieldValue::Clone() const {
	return nullptr;
}

FieldValue& FieldValue::SetBool(bool v) {
	value_ = v;
	return *this;
}

FieldValue& FieldValue::SetInt(int v) {
	value_ = v;
	return *this;
}

FieldValue& FieldValue::SetDouble(double v) {
	value_ = v;
	return *this;
}

FieldValue& FieldValue::SetString(const std::string& v) {
	value_ = v;
	return *this;
}

bool FieldValue::IsBool() const {
	return value_.index() == 1;
}

bool FieldValue::IsInt() const {
	return value_.index() == 2;
}

bool FieldValue::IsDouble() const {
	return value_.index() == 3;
}

bool FieldValue::IsString() const {
	return value_.index() == 4;
}

bool FieldValue::GetBool() const {
	try {
		return std::get<bool>(value_);
	} catch (...) {
		return false;
	}
}

int FieldValue::GetInt() const {
	try {
		return std::get<int>(value_);
	} catch (...) {
		return 0;
	}
}

double FieldValue::GetDouble() const {
	try {
		return std::get<double>(value_);
	} catch (...) {
		return 0.0;
	}
}

std::string FieldValue::GetString() const {
	try {
		return std::get<std::string>(value_);
	} catch (...) {
		return std::string();
	}
}
