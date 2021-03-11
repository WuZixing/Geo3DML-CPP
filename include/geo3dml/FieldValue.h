#pragma once

#include <variant>
#include "Field.h"

namespace geo3dml {

	class FieldValue {
	public:
		static bool IsTrue(const std::string& str);
	public:
		FieldValue();
		FieldValue(const std::string& fieldName);
		FieldValue(const std::string& fieldName, bool value);
		FieldValue(const std::string& fieldName, int value);
		FieldValue(const std::string& fieldName, double value);
		FieldValue(const std::string& fieldName, const std::string& value);
		virtual ~FieldValue();

		FieldValue& SetFieldName(const std::string& name);
		const std::string& FieldName() const;

		virtual Field::ValueType ValueType() const;
	protected:
		virtual FieldValue* Clone() const;

	public:
		FieldValue& SetBool(bool v);
		FieldValue& SetInt(int v);
		FieldValue& SetDouble(double v);
		FieldValue& SetString(const std::string& v);
		bool IsBool() const;
		bool IsInt() const;
		bool IsDouble() const;
		bool IsString() const;
		bool GetBool() const;
		int GetInt() const;
		double GetDouble() const;
		std::string GetString() const;

	private:
		std::string fieldName_;
		std::variant<std::monostate, bool, int, double, std::string> value_;
	};
}
