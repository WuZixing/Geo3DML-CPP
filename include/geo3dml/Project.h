#pragma once

#include "Geo3DML.h"
#include "Model.h"
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
		//@}

		void GetBoundingBox(double& minX, double& minY, double& minZ, double& maxX, double& maxY, double& maxZ);

		SceneStyle& GetSceneStyle();

	private:
		std::string name_;
		std::string description_;
		std::vector<Model*> models_;
		SceneStyle sceneStyle_;
	};
}