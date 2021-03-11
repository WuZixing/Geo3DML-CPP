#include <geo3dml/StyleRuleEqualTo.h>
#include <sstream>
#include <cmath>
#include <geo3dml/Utils.h>

using namespace geo3dml;

StyleRuleEqualTo::StyleRuleEqualTo(const std::string& fieldName, const std::string& valueLiteral) {
	fieldName_ = fieldName;
	valueLiteral_ = valueLiteral;
}

StyleRuleEqualTo::StyleRuleEqualTo(const Field& fieldDef, const FieldValue* value) {
	fieldName_ = fieldDef.Name();
	if (value != NULL) {
		std::ostringstream ostr;
		switch (value->ValueType()) {
		case Field::ValueType::Boolean: {
			ostr << value->GetBool();
			valueLiteral_ = ostr.str();
			break;
		}
		case Field::ValueType::Integer: {
			ostr << value->GetInt();
			valueLiteral_ = ostr.str();
			break;
		}
		case Field::ValueType::Double: {
			ostr << value->GetDouble();
			valueLiteral_ = ostr.str();
			break;
		}
		case Field::ValueType::Text: {
			ostr << value->GetString();
			valueLiteral_ = value->GetString();
			break;
		}
		default:
			break;
		}
	}
}

StyleRuleEqualTo::~StyleRuleEqualTo() {

}

void StyleRuleEqualTo::SetFieldName(const std::string& fieldName) {
	fieldName_ = fieldName;
}

std::string StyleRuleEqualTo::GetFieldName() const {
	return fieldName_;
}

void StyleRuleEqualTo::SetValueLiteral(const std::string& valueLiteral) {
	valueLiteral_ = valueLiteral;
}

std::string StyleRuleEqualTo::GetValueLiteral() const {
	return valueLiteral_;
}

bool StyleRuleEqualTo::DoesFeatureMatch(Feature* feature) const {
	if (fieldName_ == StyleRule::GetFieldOfFeatureID().Name()) {
		return valueLiteral_ == feature->GetID();
	} else {
		const geo3dml::FieldValue* fieldValue = feature->GetField(fieldName_);
		if (fieldValue == nullptr) {
			return false;
		}
		switch (fieldValue->ValueType()) {
		case Field::ValueType::Boolean: {
			return IsTrue(valueLiteral_) == fieldValue->GetBool();
		}
		case Field::ValueType::Integer: {
			int v = (int)strtol(valueLiteral_.c_str(), NULL, 10);
			return v == fieldValue->GetInt();
		}
		case Field::ValueType::Double: {
			double v = strtod(valueLiteral_.c_str(), NULL);
			return std::fabs(fieldValue->GetDouble() - v) < 1e-6;
		}
		case Field::ValueType::Text: {
			return valueLiteral_ == fieldValue->GetString();
		}
		default:
			return false;
		}
	}
}
