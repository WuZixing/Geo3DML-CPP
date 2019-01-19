#pragma once

#include "Geo3DML.h"
#include "Layer.h"
#include <vector>

namespace geo3dml {

	class Map : public Object {
	public:
		Map();
		virtual ~Map();

		//@{
		void SetName(const std::string& name);
		std::string GetName();
		void SetDescription(const std::string& s);
		std::string GetDescription();
		//@}

		//@{
		void AddLayer(Layer* layer);
		int GetLayerCount();
		Layer* GetLayerAt(int i);
		//@}

		//@{
		void SetParentProject(const std::string& id);
		std::string GetParentProject();
		//@}

	private:
		std::string name_;
		std::string description_;
		std::string parentProjectId_;
		std::vector<Layer*> layers_;
	};
}