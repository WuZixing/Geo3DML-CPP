// UTF-8编码
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
		std::string GetName() const;
		//@}

		//@{
		FeatureClass& AddField(const Field& f);
		int GetFieldCount() const;
		const Field& GetFieldAt(int i) const;
		//@}

		//@{
		FeatureClass& AddFeature(Feature* f);
		int GetFeatureCount() const;
		Feature* GetFeatureAt(int i) const;
		/// @brief 指定要素的ID，查找要素。
		/// @param id 要素的ID。
		/// @return 指向目标要素的指针。调用者不能删除该要素对象。
		Feature* GetFeature(const std::string& id) const;
		//@}

		//@{
		FeatureClass& SetParentModel(const std::string& id);
		std::string GetParentModel() const;
		//@}

		/// Compute the minimum bounding rectangle of the feature class.
		/// @return In case of an empty feature class, it will return an invalid Box3D.
		Box3D GetMinimumBoundingRectangle() const;

	private:
		std::string name_;
		std::string parentModelId_;
		std::vector<Feature*> features_;
		std::vector<Field> fields_;
	};
}
