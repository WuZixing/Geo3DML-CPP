#pragma once

#include "Geometry.h"
#include "FieldValue.h"
#include <vector>
#include <map>

namespace geo3dml {
	class Feature : public Object {
	public:
		Feature();
		virtual ~Feature();

		//@{
		Feature& SetName(const std::string& name);
		std::string GetName();
		//@}

		//@{
		Feature& AddGeometry(Geometry* g);
		int GetGeometryCount();
		Geometry* GetGeometryAt(int i);
		//@}

		//@{
		Feature& SetParentFeatureClass(const std::string& id);
		std::string GetParentFeatureClass();
		//@}

		//{@
		Feature& SetField(FieldValue* fv);
		FieldValue* GetField(const std::string& name);
		std::vector<std::string> GetFieldNames();
		//@}

		/// Compute the minimum bounding rectangle of the feature.
		/// @param minX Output the minimum X coordinate.
		/// @param minY Output the minimum Y coordinate.
		/// @param minZ Output the minimum X coordinate.
		/// @param maxX Output the maximum X coordinate.
		/// @param maxY Output the maximum Y coordinate.
		/// @param maxZ Output the maximum Z coordinate.
		/// @return In case of a feature without any valid shape, it will return false.
		bool GetMinimumBoundingRectangle(double& minX, double& minY, double& minZ, double& maxX, double& maxY, double& maxZ);

	private:
		std::string name_;
		std::string parentFeatureClassId_;
		std::vector<Geometry*> geometries_;
		std::map<std::string, geo3dml::FieldValue*> fieldValues_;
	};
}