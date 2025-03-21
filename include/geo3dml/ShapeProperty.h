// UTF-8编码
#pragma once

#include "Geo3DML.h"
#include "Field.h"
#include <vector>

namespace geo3dml {
	/// @brief 几何对象关联的属性场。
	/// @detials 属性场的定义域可以是几何对象的顶点集、边集、面片集或者体元集；其值域可以包含多个属性字段。属性字段规定了其取值类型、无效值等信息。
	/// ShapeProperty 的值域支持布尔值、整数、浮点数，以及字符串类型的属性字段。
	class ShapeProperty : public Object {
	public:
		/// @brief 属性场在几何对象上的采样位置。
		enum SamplingTarget {
			Unknown,
			Vertex,	///< 对顶点采样
			Edge,	///< 对边采样
			Face,	///< 对面片采样
			Voxel	///< 对体元采样
		};
		/// @name 采样位置枚举值对应的名字。
		///@{
		static SamplingTarget NameToSamplingTarget(const std::string& name);
		static std::string SamplingTargetToName(SamplingTarget t);
		///@}

		/// @brief 属性场的版本信息：版本号和时间戳。
		class Version {
		public:
			Version();
			virtual ~Version();

		public:
			Version & VersionNo(const std::string& v);
			std::string VersionNo() const;

			Version& Timestamp(const std::string& t);
			std::string Timestamp() const;

		private:
			std::string versionNo_;
			std::string timestamp_;
		};

	public:
		ShapeProperty();
		virtual ~ShapeProperty();

		ShapeProperty& Target(const std::string& shapeId, SamplingTarget t);
		std::string TargetShape() const;
		SamplingTarget TargetComponent() const;

		ShapeProperty& Name(const std::string& name);
		std::string Name() const;

		ShapeProperty& VersionInfo(const Version& v);
		const Version& VersionInfo() const;

		///@{
		virtual bool AddField(const Field& f);
		virtual int GetFieldCount() const;
		virtual const Field& GetFieldAt(int i) const;
		/// @brief Get field's index.
		/// @param name Name of the field.
		/// @return Returns the index of the field. In case of none existing field, -1 will be returned.
		virtual int GetFieldIndex(const std::string& name) const;
		virtual Field GetField(const std::string& name) const;
		virtual bool CheckOrAddFieldAndFillDefaultValues(const Field& field, int numberOfValues, double defaultDouble = 0, int defaultInt = 0, bool defaultBool = false, const std::string& defaultText = "");
		///@}

		/// @name Attribute setting / getting methods for target elements by field name.
		///@{
		virtual void FillDoubleValue(const std::string& fieldName, int numberOfValues, double v) = 0;
		virtual double DoubleValue(const std::string& fieldName, int targetIndex) const = 0;
		virtual ShapeProperty& DoubleValue(const std::string& fieldName, int targetIndex, double v) = 0;
		virtual void FillTextValue(const std::string& fieldName, int numberOfValues, const std::string& v) = 0;
		virtual std::string TextValue(const std::string& fieldName, int targetIndex) const = 0;
		virtual ShapeProperty& TextValue(const std::string& fieldName, int targetIndex, const std::string& v) = 0;
		virtual void FillIntValue(const std::string& fieldName, int numberOfValues, int v) = 0;
		virtual int IntValue(const std::string& fieldName, int targetIndex) const = 0;
		virtual ShapeProperty& IntValue(const std::string& fieldName, int targetIndex, int v) = 0;
		virtual void FillBooleanValue(const std::string& fieldName, int numberOfValues, bool v) = 0;
		virtual bool BooleanValue(const std::string& fieldName, int targetIndex) const = 0;
		virtual ShapeProperty& BooleanValue(const std::string& fieldName, int targetIndex, bool v) = 0;
		///@}

		/// @name Attribute setting / getting methods for target elements by field index.
		///@{
		virtual double DoubleValue(int fieldIndex, int targetIndex) const = 0;
		virtual ShapeProperty& DoubleValue(int fieldIndex, int targetIndex, double v) = 0;
		virtual std::string TextValue(int fieldIndex, int targetIndex) const = 0;
		virtual ShapeProperty& TextValue(int fieldIndex, int targetIndex, const std::string& v) = 0;
		virtual int IntValue(int fieldIndex, int targetIndex) const = 0;
		virtual ShapeProperty& IntValue(int fieldIndex, int targetIndex, int v) = 0;
		virtual bool BooleanValue(int fieldIndex, int targetIndex) const = 0;
		virtual ShapeProperty& BooleanValue(int fieldIndex, int targetIndex, bool v) = 0;
		///@}

		/// Number of values in a field.
		virtual int GetValueCount(int fieldIndex) const = 0;
		virtual int GetValueCount(const std::string& fieldName) const = 0;

	private:
		std::string name_;
		std::string targetShapeId_;
		SamplingTarget samplingTarget_;
		std::vector<Field> fields_;
		Version versionInfo_;
	};
}
