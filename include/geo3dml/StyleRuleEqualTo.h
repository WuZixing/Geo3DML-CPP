#pragma once

#include "StyleRule.h"
#include "FieldValue.h"

namespace geo3dml {

	class StyleRuleEqualTo : public StyleRule {
	public:
		/// Make the field definition for the feature ID property.
		static Field GetFieldOfFeatureID();

	public:
		/// Constructor.
		/// @param baseValue the value to be compared.
		/// @param onField the field on which a feature's will be used for comparation. Use "gml:id" to represent the ID property of a feature.
		StyleRuleEqualTo(const FieldValue* baseValue, const Field& onField);
		virtual ~StyleRuleEqualTo();

		const Field& GetField() const;
		const FieldValue* GetBaseValue() const;

		virtual bool DoesFeatureMatch(Feature* feature);

	private:
		Field targetField_;
		const FieldValue* baseValue_;
	};
}
