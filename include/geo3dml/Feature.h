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
		std::string GetName() const;
		//@}

		//@{
		Feature& AddGeometry(Geometry* g);
		int GetGeometryCount() const;
		Geometry* GetGeometryAt(int i) const;
		//@}

		//@{
		Feature& SetParentFeatureClass(const std::string& id);
		std::string GetParentFeatureClass() const;
		//@}

		//{@
		Feature& SetField(const FieldValue& fv);
		const FieldValue* GetField(const std::string& name) const;
		std::vector<std::string> GetFieldNames() const;
		//@}

		/// Compute the minimum bounding rectangle of the feature.
		/// @return In case of a feature without any valid shape, it will return an invalid Box3D.
		Box3D GetMinimumBoundingRectangle() const;

	private:
		std::string name_;
		std::string parentFeatureClassId_;
		std::vector<Geometry*> geometries_;
		std::map<std::string, geo3dml::FieldValue> fieldValues_;
	};
}