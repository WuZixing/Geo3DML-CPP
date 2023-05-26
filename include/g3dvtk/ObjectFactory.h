#pragma once

#include <geo3dml/ObjectFactory.h>

namespace g3dvtk {

	class ObjectFactory : public geo3dml::ObjectFactory {
	public:
		ObjectFactory();
		virtual ~ObjectFactory();

		/// @name Overrided methods inherited from geo3dml::ObjectFactory.
		//@{
		virtual ObjectFactory* Clone() override;

		virtual geo3dml::Project* NewProject() override;
		virtual geo3dml::Model* NewModel() override;
		virtual geo3dml::FeatureClass* NewFeatureClass() override;
		virtual geo3dml::Feature* NewFeature() override;

		virtual geo3dml::Point* NewPoint() override;
		virtual geo3dml::MultiPoint* NewMultiPoint() override;
		virtual geo3dml::LineString* NewLineString() override;
		virtual geo3dml::MultiLineString* NewMultiLineString() override;
		virtual geo3dml::TIN* NewTIN() override;
		virtual geo3dml::CornerPointGrid* NewCornerPointGrid() override;
		virtual geo3dml::CornerPointGrid* NewCornerPointGrid(int dimI, int dimJ, int dimK) override;
		virtual geo3dml::UniformGrid* NewUniformGrid() override;
		virtual geo3dml::UniformGrid* NewUniformGrid(
			double originX, double originY, double originZ,
			double stepX, double stepY, double stepZ,
			int dimI, int dimJ, int dimK
		) override;
		virtual geo3dml::Annotation* NewAnnotation() override;

		virtual geo3dml::GTPVolume* NewGTPVolume() override;

		virtual geo3dml::RectifiedGrid* NewRectifiedGrid(
			const geo3dml::Point3D& origin,
			const geo3dml::Vector3D& vecI, const geo3dml::Vector3D& vecJ, const geo3dml::Vector3D& vecK,
			int highI, int highJ, int highK, int lowI = 0, int lowJ = 0, int lowK = 0) override;
		virtual geo3dml::RectifiedGrid* NewRectifiedGrid(
			const geo3dml::Point3D& origin,
			double stepI, double stepJ, double stepK,
			int highI, int highJ, int highK, int lowI = 0, int lowJ = 0, int lowK = 0) override;

		virtual geo3dml::TetrahedronVolume* NewTetrahedronVolume() override;

		virtual geo3dml::CuboidVolume* NewCuboidVolume() override;

		virtual geo3dml::ShapeProperty* NewShapeProperty() override;

		virtual geo3dml::Actor* NewActor() override;
		//@}
	};
}