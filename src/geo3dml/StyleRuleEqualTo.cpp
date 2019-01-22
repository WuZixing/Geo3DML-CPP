#include <geo3dml/StyleRuleEqualTo.h>

using namespace geo3dml;

StyleRuleEqualTo::StyleRuleEqualTo(const FieldValue* baseValue, const Field& onField) {
	targetField_ = onField;
	baseValue_ = baseValue;
}

StyleRuleEqualTo::~StyleRuleEqualTo() {
	if (baseValue_ != NULL) {
		delete baseValue_;
	}
}

const Field& StyleRuleEqualTo::GetField() const {
	return targetField_;
}

const FieldValue* StyleRuleEqualTo::GetBaseValue() const {
	return baseValue_;
}

bool StyleRuleEqualTo::DoesFeatureMatch(Feature* feature) {
	if (targetField_.Name() == StyleRule::GetFieldOfFeatureID().Name()) {
		const TextFieldValue* textValue = dynamic_cast<const TextFieldValue*>(baseValue_);
		if (textValue != NULL) {
			return textValue->Value() == feature->GetID();
		} else {
			return false;
		}
	} else {
		switch (targetField_.DataType()) {
		case Field::Integer: {
			const IntegerFieldValue* intValue = dynamic_cast<const IntegerFieldValue*>(baseValue_);
			const IntegerFieldValue* intValueOfFeature = dynamic_cast<const IntegerFieldValue*>(feature->GetField(targetField_.Name()));
			if (intValue != NULL && intValueOfFeature != NULL) {
				return intValue->Value() == intValueOfFeature->Value();
			} else {
				return false;
			}
		}
		case Field::Double: {
			const DoubleFieldValue* doubleValue = dynamic_cast<const DoubleFieldValue*>(baseValue_);
			const DoubleFieldValue* doubleValueOfFeature = dynamic_cast<const DoubleFieldValue*>(feature->GetField(targetField_.Name()));
			if (doubleValue != NULL && doubleValueOfFeature != NULL) {
				return fabs(doubleValue->Value() - doubleValueOfFeature->Value()) < 1e-6;
			} else {
				return false;
			}
		}
		case Field::Text: {
			const TextFieldValue* textValue = dynamic_cast<const TextFieldValue*>(baseValue_);
			const TextFieldValue* textValueOfFeature = dynamic_cast<const TextFieldValue*>(feature->GetField(targetField_.Name()));
			if (textValue != NULL && textValueOfFeature != NULL) {
				return textValue->Value() == textValueOfFeature->Value();
			} else {
				return false;
			}
		}
		case Field::Boolean: {
			const BooleanFieldValue* boolValue = dynamic_cast<const BooleanFieldValue*>(baseValue_);
			const BooleanFieldValue* boolValueOfFeature = dynamic_cast<const BooleanFieldValue*>(feature->GetField(targetField_.Name()));
			if (boolValue != NULL && boolValueOfFeature != NULL) {
				return boolValue->Value() == boolValueOfFeature->Value();
			} else {
				return false;
			}
		}
		default:
			return false;
		}
	}
}
