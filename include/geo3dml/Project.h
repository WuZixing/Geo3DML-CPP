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
		const std::string& GetName() const;
		//@}

		//@{
		void SetDescription(const std::string& desc);
		const std::string& GetDescription() const;
		//@}

		//@{
		void AddModel(Model* model);
		int GetModelCount() const;
		Model* GetModelAt(int i) const;
		Model* RemoveModelAt(int i);
		FeatureClass* FindFeatureClass(const std::string& id) const;
		//@}

		//@{
		void AddMap(Map* map);
		int GetMapCount() const;
		Map* GetMapAt(int i) const;
		Map* RemoveMapAt(int i);
		void BindFeatureClassesToLayers(ObjectFactory* g3dFactory);
		//@}

		/// Compute the minimum bounding rectangle of all the models.
		/// @return In case of an empty project, it will return an invalid Box3D.
		Box3D GetMinimumBoundingRectangle() const;

		SceneStyle& GetSceneStyle();

	private:
		std::string name_;
		std::string description_;
		std::vector<Model*> models_;
		std::vector<Map*> maps_;
		SceneStyle sceneStyle_;
	};
}