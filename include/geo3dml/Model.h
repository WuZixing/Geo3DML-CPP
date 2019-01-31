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
		std::string GetName();
		//@}

		//@{
		void SetType(ModelType t);
		ModelType GetType();
		//@}

		//@{
		void AddFeatureClass(FeatureClass* f);
		int GetFeatureClassCount();
		FeatureClass* GetFeatureClassAt(int i);
		FeatureClass* GetFeatureClass(const std::string& id);
		/// Remove a feature class from the model but not delete it.
		void RemoveFeatureClass(const std::string& id);
		//@}

		/// @name Metadata.
		//@{
		std::string GetDateStamp();
		void SetDateStamp(const std::string& s);
		std::string GetDescription();
		void SetDescription(const std::string& s);
		std::string GetVersion();
		void SetVersion(const std::string& s);
		std::string GetToolName();
		void SetToolName(const std::string& s);
		std::string GetToolVersion();
		void SetToolVersion(const std::string& s);
		//@]

		//@{
		void SetMinimumBoundingRectangle(double minX, double minY, double minZ, double maxX, double maxY, double maxZ);
		/// Compute the minimum bounding rectangle of the model.
		/// @param minX Output the minimum X coordinate.
		/// @param minY Output the minimum Y coordinate.
		/// @param minZ Output the minimum X coordinate.
		/// @param maxX Output the maximum X coordinate.
		/// @param maxY Output the maximum Y coordinate.
		/// @param maxZ Output the maximum Z coordinate.
		/// @return In case of an empty model or a model without a valid bounding box, it will return false.
		bool GetMinimumBoundingRectangle(double& minX, double& minY, double& minZ, double& maxX, double& maxY, double& maxZ);
		//@}

		//@{
		void SetParentProject(const std::string& id);
		std::string GetParentProject();
		//@}

	private:
		std::string name_;
		ModelType type_;
		std::vector<FeatureClass*> featureClasses_;
		double box_[6];	///< [minX, minY, minZ, maxX, maxY, maxZ]
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

