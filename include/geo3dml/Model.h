// UTF-8编码
#pragma once

#include "FeatureClass.h"
#include "Metadata.h"

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
		void AddFeatureClass(FeatureClass* f);
		int GetFeatureClassCount() const;
		FeatureClass* GetFeatureClassAt(int i) const;
		FeatureClass* GetFeatureClass(const std::string& id) const;
		/// Remove a feature class from the model but not delete it.
		void RemoveFeatureClass(const std::string& id);
		///@}

		/// @name 元数据。
		///@{
		void SetMetadata(const Metadata& meta);
		const Metadata& GetMetadata() const;
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
		Metadata metadata_;
		std::string parentProjectId_;
	};
}

