#pragma once

#include "Geo3DML.h"
#include "FeatureClass.h"
#include "Style.h"
#include "Actor.h"

namespace geo3dml {

	class ObjectFactory;

	class Layer : public Object {
	public:
		Layer();
		virtual ~Layer();

		//@{
		void SetName(const std::string& name);
		std::string GetName() const;
		//@}

		//@{
		void BindFeatureClass(FeatureClass* fc);
		FeatureClass* GetBindingFeatureClass() const;
		void SetBindingFeatureClassID(const std::string& featureClassID);
		std::string GetBindingFeatureClassID() const;
		//@}

		void AddStyle(Style* style);
		int GetStyleCount() const;
		Style* GetStyleAt(int i) const;

		void AddActor(Actor* actor);
		int GetActorCount() const;
		Actor* GetActorAt(int i) const;
		void BuildActorsFromFeatures(ObjectFactory* g3dFactory);
		void RebuildActorsFromFeaturesByStyle(int styleIndex, ObjectFactory* g3dFactory);

		//@{
		void SetParentMap(const std::string& id);
		std::string GetParentMap() const;
		//@}

		/// Compute the minimum bounding rectangle of the feature class.
		/// @return In case of an empty feature class, it will return an invalid Box3D.
		Box3D GetMinimumBoundingRectangle() const;

	private:
		void DeleteAllActors();

	private:
		std::string name_;
		FeatureClass* bindingFeatureClass_;
		std::string bindingFeatureClassID_;
		std::string parentMapId_;
		std::vector<Style*> styles_;
		std::vector<Actor*> actors_;
	};
}
