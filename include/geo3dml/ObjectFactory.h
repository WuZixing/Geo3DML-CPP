#pragma once

#include "Project.h"
#include "Model.h"
#include "FeatureClass.h"
#include "Feature.h"
#include "TIN.h"
#include "CornerPointGrid.h"
#include "UniformGrid.h"
#include "LineString.h"
#include "Point.h"
#include "MultiPoint.h"
#include "Map.h"
#include "PointSymbolizer.h"
#include "LineSymbolizer.h"
#include "SurfaceSymbolizer.h"
#include "GeoDiscreteCoverageSymbolizer.h"
#include "FeatureTypeStyle.h"
#include "Annotation.h"

namespace geo3dml {
	/// Factory for Geo3DML objects. It is not thread safe.
	class ObjectFactory {
	public:
		static std::string TypeNameOfGeometry(Geometry* shape);

	public:
		ObjectFactory();
		virtual ~ObjectFactory();

		/// Clone the ObjectFactory itself.
		virtual ObjectFactory* Clone() = 0;

		/// @name model objects.
		//@{
		virtual Project* NewProject() = 0;
		virtual Model* NewModel() = 0;
		virtual FeatureClass* NewFeatureClass() = 0;
		virtual Feature* NewFeature() = 0;
		//@}

		/// @name goemetry(shape) objects.
		//@{
		virtual Point* NewPoint() = 0;
		virtual MultiPoint* NewMultiPoint() = 0;
		virtual LineString* NewLineString() = 0;
		virtual TIN* NewTIN() = 0;
		virtual CornerPointGrid* NewCornerPointGrid() = 0;
		virtual CornerPointGrid* NewCornerPointGrid(int dimI, int dimJ, int dimK) = 0;
		virtual UniformGrid* NewUniformGrid() = 0;
		virtual UniformGrid* NewUniformGrid(
			double originX, double originY, double originZ,
			double stepX, double stepY, double stepZ,
			int dimI, int dimJ, int dimK
		) = 0;
		virtual Annotation* NewAnnotation() = 0;
		//@}

		/// @name shape property.
		//@{
		virtual ShapeProperty* NewShapeProperty() = 0;
		//@}

		/// @name map
		//@{
		virtual Map* NewMap();
		virtual Layer* NewLayer();
		virtual Actor* NewActor() = 0;
		virtual PointSymbolizer* NewPointSymbolizer();
		virtual LineSymbolizer* NewLineSymbolizer();
		virtual SurfaceSymbolizer* NewSurfaceSymbolizer();
		virtual GeoDiscreteCoverageSymbolizer* NewGeoDiscreteCoverageSymbolizer();
		virtual FeatureTypeStyle* NewFeatureTypeStyle();
		//@}

	public:
		Geometry* NewGeometry(const std::string& typeName);
	};
}
