// UTF-8编码
#pragma once

#include "FeatureClass.h"
#include "FeatureRelation.h"
#include "ModelMetadata.h"

namespace geo3dml {

	class Model : public Object {
	public:
		enum ModelType {
			Other,
			Drill,
			Section,
			Model3D,
			Isogram
		};
		static ModelType NameToModelType(const std::string& n);
		static std::string ModelTypeToName(ModelType t);

	public:
		Model();
		virtual ~Model();

		///@{
		void SetName(const std::string& name);
		const std::string& GetName() const;
		///@}

		///@{
		void SetType(ModelType t);
		ModelType GetType() const;
		///@}

		///@{
		/// @brief 向模型中添加一个要素类。
		/// @param f 新添加的要素类对象。该要素类对象将由本模型对象负责管理。
		void AddFeatureClass(FeatureClass* f);
		int GetFeatureClassCount() const;
		FeatureClass* GetFeatureClassAt(int i) const;
		FeatureClass* GetFeatureClass(const std::string& id) const;
		/// Remove a feature class from the model but not delete it.
		void RemoveFeatureClass(const std::string& id);
		///@}

		/// @name 要素之间的关系。
		///@{
		/// @brief 添加一个要素关系。
		/// @param fr 新添加的要素关系对象。该要素关系对象将由本模型对象负责管理。
		void AddFeatureRelation(FeatureRelation* fr);
		/// @brief 取模型中记录的要素关系的数目。
		/// @return 模型中要素关系的数目。
		int GetFeatureRelationCount() const;
		/// @brief 取模型中的要素关系。
		/// @param i 要素关系对象的索引位置（从0开始计数）。
		/// @return 指向要素关系对象的指针。返回的要素关系对象仍由本对象负责管理。
		FeatureRelation* GetFeatureRelation(int i) const;
		/// @brief 从模型中移除要素关系对象，但是不删除它。
		/// @param i 要被移除的要素关系对象的索引位置（从0开始计数）。
		/// @return 返回指向被移除的对象的指针。该对象的内存将由调用者负责管理。
		FeatureRelation* RemoveFeatureRelation(int i);
		///@}

		/// @name 元数据。
		///@{
		void SetMetadata(const ModelMetadata& meta);
		const ModelMetadata& GetMetadata() const;
		///@}
		
		///@{
		/// Compute the minimum bounding rectangle of the model.
		/// @return In case of an empty model or a model without a valid bounding box, it will return an invalid Box3D.
		Box3D GetMinimumBoundingRectangle() const;
		///@}

		///@{
		void SetParentProject(const std::string& id);
		const std::string& GetParentProject() const;
		///@}

	private:
		std::string name_;
		ModelType type_;
		std::vector<FeatureClass*> featureClasses_;
		std::vector<FeatureRelation*> featureRelations_;
		ModelMetadata metadata_;
		std::string parentProjectId_;
	};
}

