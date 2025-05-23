#pragma once

#include <geo3dml/ShapeProperty.h>
#include <vtkSmartPointer.h>
#include <vtkDataSetAttributes.h>

namespace g3dvtk {

	class ShapeProperty : public geo3dml::ShapeProperty {
	public:
		ShapeProperty();
		virtual ~ShapeProperty();

		void BindDataSet(vtkDataSetAttributes* ds);

	public:
		virtual bool AddField(const geo3dml::Field& f);

		/// @name Attribute setting / getting methods for target elements by field name.
		//@{
		virtual void FillDoubleValue(const std::string& fieldName, int numberOfValues, double v);
		virtual double DoubleValue(const std::string& fieldName, int targetIndex) const;
		virtual ShapeProperty& DoubleValue(const std::string& fieldName, int targetIndex, double v);
		virtual void FillTextValue(const std::string& fieldName, int numberOfValues, const std::string& v);
		virtual std::string TextValue(const std::string& fieldName, int targetIndex) const;
		virtual ShapeProperty& TextValue(const std::string& fieldName, int targetIndex, const std::string& v);
		virtual void FillIntValue(const std::string& fieldName, int numberOfValues, int v);
		virtual int IntValue(const std::string& fieldName, int targetIndex) const;
		virtual ShapeProperty& IntValue(const std::string& fieldName, int targetIndex, int v);
		virtual void FillBooleanValue(const std::string& fieldName, int numberOfValues, bool v);
		virtual bool BooleanValue(const std::string& fieldName, int targetIndex) const;
		virtual ShapeProperty& BooleanValue(const std::string& fieldName, int targetIndex, bool v);
		//@}

		/// @name Attribute setting / getting methods for target elements by field index.
		//@{
		virtual double DoubleValue(int fieldIndex, int targetIndex) const;
		virtual ShapeProperty& DoubleValue(int fieldIndex, int targetIndex, double v);
		virtual std::string TextValue(int fieldIndex, int targetIndex) const;
		virtual ShapeProperty& TextValue(int fieldIndex, int targetIndex, const std::string& v);
		virtual int IntValue(int fieldIndex, int targetIndex) const;
		virtual ShapeProperty& IntValue(int fieldIndex, int targetIndex, int v);
		virtual bool BooleanValue(int fieldIndex, int targetIndex) const;
		virtual ShapeProperty& BooleanValue(int fieldIndex, int targetIndex, bool v);
		//@}

		virtual int GetValueCount(int fieldIndex) const;
		virtual int GetValueCount(const std::string& fieldName) const;

	private:
		std::string GetTemporaryNameOfField(int fieldIndex) const;

	private:
		vtkSmartPointer<vtkDataSetAttributes> dataSet_;
		int baseIndexOfFields_;	///!< vtkDatasetAttributes may hava some default attibutes for ghost cells etc., additional fields would be appended to the existing fields.
	};
}
