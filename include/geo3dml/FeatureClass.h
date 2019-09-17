#pragma once

#include "Geo3DML.h"
#include "Field.h"
#include "Feature.h"
#include <vector>

namespace geo3dml {
	class FeatureClass : public Object {
	public:
		FeatureClass();
		virtual ~FeatureClass();

		//@{
		FeatureClass& SetName(const std::string& name);
		std::string GetName();
		//@}

		//@{
		FeatureClass& AddField(const Field& f);
		int GetFieldCount();
		const Field& GetFieldAt(int i);
		//@}

		//@{
		FeatureClass& AddFeature(Feature* f);
		int GetFeatureCount();
		Feature* GetFeatureAt(int i);
		Feature* GetFeature(const std::string& id);
		//@}

		//@{
		FeatureClass& SetParentModel(const std::string& id);
		std::string GetParentModel();
		//@}

		/// Compute the minimum bounding rectangle of the feature class.
		/// @param minX Output the minimum X coordinate.
		/// @param minY Output the minimum Y coordinate.
		/// @param minZ Output the minimum X coordinate.
		/// @param maxX Output the maximum X coordinate.
		/// @param maxY Output the maximum Y coordinate.
		/// @param maxZ Output the maximum Z coordinate.
		/// @return In case of an empty feature class, it will return false.
		bool GetMinimumBoundingRectangle(double& minX, double& minY, double& minZ, double& maxX, double& maxY, double& maxZ);

	private:
		std::string name_;
		std::string parentModelId_;
		std::vector<Feature*> features_;
		std::vector<Field> fields_;
	};
}
