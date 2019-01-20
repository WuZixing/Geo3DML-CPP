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
		std::string description_;
		std::string parentProjectId_;
		std::vector<Layer*> layers_;
		double box_[6];	///< [minX, minY, minZ, maxX, maxY, maxZ]
	};
}