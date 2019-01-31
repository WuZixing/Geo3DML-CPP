#pragma once

#include "Geo3DML.h"
#include "Model.h"
#include "Map.h"
#include "SceneStyle.h"

namespace geo3dml {
	/// 工程对象
	class Project : public Object {
	public:
		Project();
		virtual ~Project();

		//@{
		void SetName(const std::string& name);
		std::string GetName();
		//@}

		//@{
		void SetDescription(const std::string& desc);
		std::string GetDescription();
		//@}

		//@{
		void AddModel(Model* model);
		int GetModelCount();
		Model* GetModelAt(int i);
		Model* RemoveModelAt(int i);
		FeatureClass* FindFeatureClass(const std::string& id);
		//@}

		//@{
		void AddMap(Map* map);
		int GetMapCount();
		Map* GetMapAt(int i);
		Map* RemoveMapAt(int i);
		void BindFeatureClassesToLayers(ObjectFactory* g3dFactory);
		//@}

		/// Compute the minimum bounding rectangle of all the models.
		/// @param minX Output the minimum X coordinate.
		/// @param minY Output the minimum Y coordinate.
		/// @param minZ Output the minimum X coordinate.
		/// @param maxX Output the maximum X coordinate.
		/// @param maxY Output the maximum Y coordinate.
		/// @param maxZ Output the maximum Z coordinate.
		/// @return In case of an empty project, it will return false.
		bool GetMinimumBoundingRectangle(double& minX, double& minY, double& minZ, double& maxX, double& maxY, double& maxZ);

		SceneStyle& GetSceneStyle();

	private:
		std::string name_;
		std::string description_;
		std::vector<Model*> models_;
		std::vector<Map*> maps_;
		SceneStyle sceneStyle_;
	};
}