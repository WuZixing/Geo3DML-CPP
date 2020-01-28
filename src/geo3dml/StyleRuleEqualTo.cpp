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
		const IntegerFieldValue* intValue = dynamic_cast<const IntegerFieldValue*>(value);
		if (intValue != NULL) {
			ostr << intValue->Value();
			valueLiteral_ = ostr.str();
		} else {
			const DoubleFieldValue* doubleValue = dynamic_cast<const DoubleFieldValue*>(value);
			if (doubleValue != NULL) {
				ostr << doubleValue->Value();
				valueLiteral_ = ostr.str();
			} else {
				const TextFieldValue* textValue = dynamic_cast<const TextFieldValue*>(value);
				if (textValue != NULL) {
					valueLiteral_ = textValue->Value();
				} else {
					const BooleanFieldValue* boolValue = dynamic_cast<const BooleanFieldValue*>(value);
					if (boolValue != NULL) {
						ostr << boolValue->Value();
						valueLiteral_ = ostr.str();
					}
				}
			}
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
		geo3dml::FieldValue* fieldValue = feature->GetField(fieldName_);
		if (fieldValue != NULL) {
			const IntegerFieldValue* intValue = dynamic_cast<const IntegerFieldValue*>(fieldValue);
			if (intValue != NULL) {
				int v = (int)strtol(valueLiteral_.c_str(), NULL, 10);
				return v == intValue->Value();
			} else {
				const DoubleFieldValue* doubleValue = dynamic_cast<const DoubleFieldValue*>(fieldValue);
				if (doubleValue != NULL) {
					double v = strtod(valueLiteral_.c_str(), NULL);
					return std::fabs(doubleValue->Value() - v) < 1e-6;
				} else {
					const TextFieldValue* textValue = dynamic_cast<const TextFieldValue*>(fieldValue);
					if (textValue != NULL) {
						return valueLiteral_ == textValue->Value();
					} else {
						const BooleanFieldValue* boolValue = dynamic_cast<const BooleanFieldValue*>(fieldValue);
						if (boolValue != NULL) {
							return IsTrue(valueLiteral_) == boolValue->Value();
						} else {
							return false;
						}
					}
				}
			}
		} else {
			return false;
		}
	}
}
