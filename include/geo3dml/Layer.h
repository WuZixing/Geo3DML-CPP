#pragma once

#include "Geo3DML.h"
#include "FeatureClass.h"
#include "Geo3DStyle.h"
#include "Actor.h"

namespace geo3dml {

	class Layer : public Object {
	public:
		Layer();
		virtual ~Layer();

		//@{
		void SetName(const std::string& name);
		std::string GetName();
		//@}

		//@{
		void BindFeatureClass(FeatureClass* fc);
		FeatureClass* GetBindingFeatureClass();
		void SetBindingFeatureClassID(const std::string& featureClassID);
		std::string GetBindingFeatureClassID();
		//@}

		void AddStyle(Geo3DStyle* style);
		int GetStyleCount();
		Geo3DStyle* GetStyleAt(int i);

		void AddActor(Actor* actor);
		int GetActorCount();
		Actor* GetActorAt(int i);
		void RebuildActorsFromFeaturesByStyle(int styleIndex, ObjectFactory* g3dFactory);

		//@{
		void SetParentMap(const std::string& id);
		std::string GetParentMap();
		//@}

		/// Compute the minimum bounding rectangle of the feature class.
		/// @param minX Output the minimum X coordinate.
		/// @param minY Output the minimum Y coordinate.
		/// @param minZ Output the minimum X coordinate.
		/// @param maxX Output the maximum X coordinate.
		/// @param maxY Output the maximum Y coordinate.
		/// @param maxZ Output the maximum Z coordinate.
		/// @return In case of an empty feature class, it will return false.
		bool GetMinimumBoundingRectangle(double& minX, double& minY, double& minZ, double& maxX, double& maxY, double& maxZ);

	private:
		void DeleteAllActors();

	private:
		std::string name_;
		FeatureClass* bindingFeatureClass_;
		std::string bindingFeatureClassID_;
		std::string parentMapId_;
		std::vector<Geo3DStyle*> styles_;
		std::vector<Actor*> actors_;
	};
}
