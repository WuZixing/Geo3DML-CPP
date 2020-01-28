#pragma once

#include "StyleRule.h"
#include "FieldValue.h"

namespace geo3dml {

	class StyleRuleEqualTo : public StyleRule {
	public:
		/// Constructor.
		/// @param fieldName the field on which a feature's attribute will be used for comparation. Use "gml:id" to represent the ID property of a feature.
		/// @param valueLiteral the value to be compared.
		StyleRuleEqualTo(const std::string& fieldName = "", const std::string& valueLiteral = "");
		StyleRuleEqualTo(const Field& fieldDef, const FieldValue* value);
		virtual ~StyleRuleEqualTo();

		void SetFieldName(const std::string& fieldName);
		std::string GetFieldName() const;
		void SetValueLiteral(const std::string& valueLiteral);
		std::string GetValueLiteral() const;

		virtual bool DoesFeatureMatch(Feature* feature) const;

	private:
		std::string fieldName_, valueLiteral_;
	};
}
