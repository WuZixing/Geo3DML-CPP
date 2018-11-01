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
		//@}

		//@{
		FeatureClass& SetParentModel(const std::string& id);
		std::string GetParentModel();
		//@}

	private:
		std::string name_;
		std::string parentModelId_;
		std::vector<Feature*> features_;
		std::vector<Field> fields_;
	};
}
