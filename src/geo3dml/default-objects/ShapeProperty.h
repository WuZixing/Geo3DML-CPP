// UTF-8编码
#pragma once

#include <geo3dml/ShapeProperty.h>
#include <map>

namespace geo3dml {
    namespace geometry {
        /// @brief 几何对象关联的属性场。
        class ShapeProperty : public geo3dml::ShapeProperty {
        public:
            ShapeProperty();
            virtual ~ShapeProperty();

        public:
            ///@name 实现父类定义的接口。
            ///@{
			virtual void FillDoubleValue(const std::string& fieldName, int numberOfValues, double v) override;
			virtual double DoubleValue(const std::string& fieldName, int targetIndex) const override;
			virtual geo3dml::ShapeProperty& DoubleValue(const std::string& fieldName, int targetIndex, double v) override;
			virtual void FillTextValue(const std::string& fieldName, int numberOfValues, const std::string& v) override;
			virtual std::string TextValue(const std::string& fieldName, int targetIndex) const override;
			virtual geo3dml::ShapeProperty& TextValue(const std::string& fieldName, int targetIndex, const std::string& v) override;
			virtual void FillIntValue(const std::string& fieldName, int numberOfValues, int v) override;
			virtual int IntValue(const std::string& fieldName, int targetIndex) const override;
			virtual geo3dml::ShapeProperty& IntValue(const std::string& fieldName, int targetIndex, int v) override;
			virtual void FillBooleanValue(const std::string& fieldName, int numberOfValues, bool v) override;
			virtual bool BooleanValue(const std::string& fieldName, int targetIndex) const override;
			virtual geo3dml::ShapeProperty& BooleanValue(const std::string& fieldName, int targetIndex, bool v) override;

			virtual double DoubleValue(int fieldIndex, int targetIndex) const override;
			virtual geo3dml::ShapeProperty& DoubleValue(int fieldIndex, int targetIndex, double v) override;
			virtual std::string TextValue(int fieldIndex, int targetIndex) const override;
			virtual geo3dml::ShapeProperty& TextValue(int fieldIndex, int targetIndex, const std::string& v) override;
			virtual int IntValue(int fieldIndex, int targetIndex) const override;
			virtual geo3dml::ShapeProperty& IntValue(int fieldIndex, int targetIndex, int v) override;
			virtual bool BooleanValue(int fieldIndex, int targetIndex) const override;
			virtual geo3dml::ShapeProperty& BooleanValue(int fieldIndex, int targetIndex, bool v) override;

			virtual int GetValueCount(int fieldIndex) const override;
			virtual int GetValueCount(const std::string& fieldName) const override;
            ///@}

		private:
			/// @brief 整数类型的属性字段的值。键是字段定义在数组中的索引号。
			std::map<int, std::vector<int>> intFields_;
			/// @brief 双精度浮点数类型的属性字段的值。
			std::map<int, std::vector<double>> doubleFields_;
			/// @brief 布尔值类型的属性字段的值。
			std::map<int, std::vector<bool>> boolFields_;
			/// @brief 字符串类型的属性字段的值。
			std::map<int, std::vector<std::string>> textFields_;
        };
    }
}
