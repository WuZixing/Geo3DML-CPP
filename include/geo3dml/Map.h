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
		std::string GetName() const;
		void SetDescription(const std::string& s);
		std::string GetDescription() const;
		//@}

		//@{
		void AddLayer(Layer* layer);
		int GetLayerCount() const;
		Layer* GetLayerAt(int i) const;
		//@}

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
		std::string description_;
		std::string parentProjectId_;
		std::vector<Layer*> layers_;
	};
}