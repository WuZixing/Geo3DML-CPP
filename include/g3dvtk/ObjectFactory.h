#pragma once

#include <geo3dml/ObjectFactory.h>

namespace g3dvtk {

	class ObjectFactory : public geo3dml::ObjectFactory {
	public:
		ObjectFactory();
		virtual ~ObjectFactory();

		/// @name Overrided methods inherited from geo3dml::ObjectFactory.
		//@{
		virtual ObjectFactory* Clone();

		virtual geo3dml::Project* NewProject();
		virtual geo3dml::Model* NewModel();
		virtual geo3dml::FeatureClass* NewFeatureClass();
		virtual geo3dml::Feature* NewFeature();

		virtual geo3dml::Point* NewPoint();
		virtual geo3dml::MultiPoint* NewMultiPoint();
		virtual geo3dml::LineString* NewLineString();
		virtual geo3dml::TIN* NewTIN();
		virtual geo3dml::CornerPointGrid* NewCornerPointGrid();
		virtual geo3dml::CornerPointGrid* NewCornerPointGrid(int dimI, int dimJ, int dimK);
		virtual geo3dml::UniformGrid* NewUniformGrid();
		virtual geo3dml::UniformGrid* NewUniformGrid(
			double originX, double originY, double originZ,
			double stepX, double stepY, double stepZ,
			int dimI, int dimJ, int dimK
		);
		virtual geo3dml::Annotation* NewAnnotation();

		virtual geo3dml::ShapeProperty* NewShapeProperty();

		virtual geo3dml::Actor* NewActor();
		//@}
	};
}