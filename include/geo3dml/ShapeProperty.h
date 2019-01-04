#pragma once

#include "Geo3DML.h"
#include "Field.h"
#include <vector>

namespace geo3dml {

	class ShapeProperty : public Object {
	public:
		enum SamplingTarget {
			Unknown,
			Vertex,
			Edge,
			Face,
			Voxel
		};
		static SamplingTarget NameToSamplingTarget(const std::string& name);
		static std::string SamplingTargetToName(SamplingTarget t);

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
		std::string TargetShape();
		SamplingTarget TargetComponent();

		ShapeProperty& Name(const std::string& name);
		std::string Name();

		ShapeProperty& VersionInfo(const Version& v);
		const Version& VersionInfo();

		//@{
		virtual bool AddField(const Field& f);
		virtual int GetFieldCount();
		virtual const Field& GetFieldAt(int i);
		/// @brief Get field's index.
		/// @param name Name of the field.
		/// @return Returns the index of the field. In case of none existing field, -1 will be returned.
		virtual int GetFieldIndex(const std::string& name);
		virtual Field GetField(const std::string& name);
		virtual bool CheckOrAddFieldAndFillDefaultValues(const Field& field, int numberOfValues, double defaultDouble = 0, int defaultInt = 0, bool defaultBool = false, const std::string& defaultText = "");
		//@}

		/// @name Attribute setting / getting methods for target elements by field name.
		//@{
		virtual void FillDoubleValue(const std::string field, int numberOfValues, double v) = 0;
		virtual double DoubleValue(const std::string& field, int targetIndex) = 0;
		virtual ShapeProperty& DoubleValue(const std::string& field, int targetIndex, double v) = 0;
		virtual void FillTextValue(const std::string& field, int numberOfValues, const std::string& v) = 0;
		virtual std::string TextValue(const std::string& field, int targetIndex) = 0;
		virtual ShapeProperty& TextValue(const std::string& field, int targetIndex, const std::string& v) = 0;
		virtual void FillIntValue(const std::string& field, int numberOfValues, int v) = 0;
		virtual int IntValue(const std::string& field, int targetIndex) = 0;
		virtual ShapeProperty& IntValue(const std::string& field, int targetIndex, int v) = 0;
		virtual void FillBooleanValue(const std::string& field, int numberOfValues, bool v) = 0;
		virtual bool BooleanValue(const std::string& field, int targetIndex) = 0;
		virtual ShapeProperty& BooleanValue(const std::string& field, int targetIndex, bool v) = 0;
		//@}

		/// @name Attribute setting / getting methods for target elements by field index.
		//@{
		virtual double DoubleValue(int fieldIndex, int targetIndex) = 0;
		virtual ShapeProperty& DoubleValue(int fieldIndex, int targetIndex, double v) = 0;
		virtual std::string TextValue(int fieldIndex, int targetIndex) = 0;
		virtual ShapeProperty& TextValue(int fieldIndex, int targetIndex, const std::string& v) = 0;
		virtual int IntValue(int fieldIndex, int targetIndex) = 0;
		virtual ShapeProperty& IntValue(int fieldIndex, int targetIndex, int v) = 0;
		virtual bool BooleanValue(int fieldIndex, int targetIndex) = 0;
		virtual ShapeProperty& BooleanValue(int fieldIndex, int targetIndex, bool v) = 0;
		//@}

		/// Number of values in a field.
		virtual int GetValueCount(int fieldIndex) = 0;
		virtual int GetValueCount(const std::string& fieldName) = 0;

	private:
		std::string name_;
		std::string targetShapeId_;
		SamplingTarget samplingTarget_;
		std::vector<Field> fields_;
		Version versionInfo_;
	};
}
