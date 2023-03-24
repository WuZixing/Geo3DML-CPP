#pragma once

#include <string>

namespace geo3dml {

	class Field {
	public:
		enum ValueType {
			Unknown,
			Text,
			Integer,
			Double,
			Boolean,
			Object
		};

		static std::string ValueTypeToName(ValueType t);
		static ValueType NameToValueType(const std::string& name);

	public:
		Field();
		Field(const Field& f);
		virtual ~Field();

		/// @name Name is the formal name of the field.
		//@{
		Field& Name(const std::string& s);
		std::string Name() const;
		//@}

		/// @name Label is a human readable name of the field.
		//@{
		Field& Label(const std::string& s);
		std::string Label() const;
		//@}

		Field& DataType(ValueType t);
		ValueType DataType() const;

		Field& Uom(const std::string& s);
		std::string Uom() const;

		Field& Definition(const std::string& s);
		std::string Definition() const;

		Field& Description(const std::string& s);
		std::string Description() const;

		Field& NoDataValue(const std::string& v);
		const std::string& NoDataValue() const;

	private:
		std::string name_;
		std::string label_;
		ValueType valueType_;
		std::string uom_;
		std::string definition_;
		std::string description_;
		std::string noDataValue_;
	};
}
