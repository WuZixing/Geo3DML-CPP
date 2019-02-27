#pragma once

#include <string>
#include "Field.h"

namespace geo3dml {

	class FieldValue {
	public:
		FieldValue(const std::string& fieldName);
		virtual ~FieldValue();

		const std::string& FieldName() const;

		virtual Field::ValueType ValueType() const = 0;

	private:
		std::string fieldName_;
	};

	class TextFieldValue : public FieldValue {
	public:
		TextFieldValue(const std::string& fieldName);
		TextFieldValue(const TextFieldValue& v);
		virtual ~TextFieldValue();

		virtual Field::ValueType ValueType() const;

		TextFieldValue& Value(const std::string& v);
		const std::string& Value() const;

	private:
		std::string value_;
	};

	class DoubleFieldValue : public FieldValue {
	public:
		DoubleFieldValue(const std::string& fieldName);
		DoubleFieldValue(const DoubleFieldValue& v);
		virtual ~DoubleFieldValue();

		virtual Field::ValueType ValueType() const;

		DoubleFieldValue& Value(double v);
		double Value() const;

	private:
		double value_;
	};

	class IntegerFieldValue : public FieldValue {
	public:
		IntegerFieldValue(const std::string& fieldName);
		IntegerFieldValue(const IntegerFieldValue& v);
		virtual ~IntegerFieldValue();

		virtual Field::ValueType ValueType() const;

		IntegerFieldValue& Value(int v);
		int Value() const;

	private:
		int value_;
	};

	class BooleanFieldValue : public FieldValue {
	public:
		BooleanFieldValue(const std::string& fieldName);
		BooleanFieldValue(const BooleanFieldValue& v);
		virtual ~BooleanFieldValue();

		virtual Field::ValueType ValueType() const;

		BooleanFieldValue& Value(bool v);
		bool Value() const;

	private:
		bool value_;
	};
}
