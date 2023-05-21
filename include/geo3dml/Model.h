#pragma once

#include "Geo3DML.h"
#include "FeatureClass.h"
#include <vector>

namespace geo3dml {

	class Model : public Object {
	public:
		enum ModelType {
			Other,
			Drill,
			Section,
			Model3D,
			Isogram
		};
		static ModelType NameToModelType(const std::string& n);
		static std::string ModelTypeToName(ModelType t);

	public:
		Model();
		virtual ~Model();

		//@{
		void SetName(const std::string& name);
		std::string GetName() const;
		//@}

		//@{
		void SetType(ModelType t);
		ModelType GetType() const;
		//@}

		//@{
		void AddFeatureClass(FeatureClass* f);
		int GetFeatureClassCount() const;
		FeatureClass* GetFeatureClassAt(int i) const;
		FeatureClass* GetFeatureClass(const std::string& id) const;
		/// Remove a feature class from the model but not delete it.
		void RemoveFeatureClass(const std::string& id);
		//@}

		/// @name Metadata.
		//@{
		std::string GetDateStamp() const;
		void SetDateStamp(const std::string& s);
		std::string GetDescription() const;
		void SetDescription(const std::string& s);
		std::string GetVersion() const;
		void SetVersion(const std::string& s);
		std::string GetToolName() const;
		void SetToolName(const std::string& s);
		std::string GetToolVersion() const;
		void SetToolVersion(const std::string& s);
		//@]

		//@{
		/// Compute the minimum bounding rectangle of the model.
		/// @return In case of an empty model or a model without a valid bounding box, it will return an invalid Box3D.
		Box3D GetMinimumBoundingRectangle() const;
		//@}

		//@{
		void SetParentProject(const std::string& id);
		std::string GetParentProject() const;
		//@}

	private:
		std::string name_;
		ModelType type_;
		std::vector<FeatureClass*> featureClasses_;
		// metadata
		std::string dateStamp_;
		std::string description_;
		std::string version_;
		std::string toolName_;
		std::string toolVersion_;
		// TODO: Spatial Reference System

		std::string parentProjectId_;
	};
}

