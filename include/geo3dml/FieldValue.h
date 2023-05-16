#pragma once

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

		Field::ValueType ValueType() const;

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
		union Value {
			bool vBool;
			int vInt;
			double vDouble;
		};
		Value value_;
		std::string strValue_;
		Field::ValueType valueType_;
	};
}
