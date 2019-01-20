#pragma once

#include "Geo3DML.h"
#include "FeatureClass.h"
#include "Geo3DStyle.h"

namespace geo3dml {

	class Layer : public Object {
	public:
		Layer();
		virtual ~Layer();

		//@{
		void SetName(const std::string& name);
		std::string GetName();
		//@}

		void BindFeatureClass(FeatureClass* fc);
		FeatureClass* GetBindingFeatureClass();

		void AddStyle(Geo3DStyle* style);
		int GetStyleCount();
		Geo3DStyle* GetStyleAt(int i);

		//@{
		void SetParentMap(const std::string& id);
		std::string GetParentMap();
		//@}

	private:
		std::string name_;
		FeatureClass* bindingFeatureClass_;
		std::string parentMapId_;
		std::vector<Geo3DStyle*> styles_;
	};
}
