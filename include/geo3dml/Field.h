// UTF-8编码
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
			Category,	// 处理gml:Category。其值为字符串，一般是来自预定义的类别名字集合。
			Object
		};

		static std::string ValueTypeToName(ValueType t);
		static ValueType NameToValueType(const std::string& name);

	public:
		Field();
		Field(const Field& f);
		virtual ~Field();

		/// @name 字段的标准名字。可用作数据库表的字段定义。
		///@{
		Field& Name(const std::string& s);
		const std::string& Name() const;
		///@}

		/// @name 字段的别名，或者显示名称。
		///@{
		Field& Label(const std::string& s);
		const std::string& Label() const;
		///@}

		Field& DataType(ValueType t);
		ValueType DataType() const;

		/// @name 字段值的单位。
		///@{
		Field& Uom(const std::string& s);
		const std::string& Uom() const;
		///@}

		/// @name 字段的规范语义定义。
		///@{
		Field& Definition(const std::string& s);
		const std::string& Definition() const;
		///@}

		/// @name 字段的说明信息。
		///@{
		Field& Description(const std::string& s);
		const std::string& Description() const;
		///@}

		/// @name 字段的无效值。统一使用字符串形式记录。
		///@{
		Field& NoDataValue(const std::string& v);
		const std::string& NoDataValue() const;
		int NoDataAsInt() const;
		double NoDataAsDouble() const;
		bool NoDataAsBool() const;
		///@}

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
