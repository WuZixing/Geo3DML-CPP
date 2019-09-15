#include <g3dvtk/ObjectFactory.h>
#include <g3dvtk/TIN.h>
#include <g3dvtk/CornerPointGrid.h>
#include <g3dvtk/UniformGrid.h>
#include <g3dvtk/LineString.h>
#include <g3dvtk/ShapeProperty.h>
#include <g3dvtk/Point.h>
#include <g3dvtk/MultiPoint.h>
#include <g3dvtk/Actor.h>
#include <g3dvtk/Annotation.h>

using namespace g3dvtk;

ObjectFactory::ObjectFactory() {

}

ObjectFactory::~ObjectFactory() {

}

ObjectFactory* ObjectFactory::Clone() {
	return new ObjectFactory();
}

geo3dml::Project* ObjectFactory::NewProject() {
	return new geo3dml::Project();
}

geo3dml::Model* ObjectFactory::NewModel() {
	return new geo3dml::Model();
}

geo3dml::FeatureClass* ObjectFactory::NewFeatureClass() {
	return new geo3dml::FeatureClass();
}

geo3dml::Feature* ObjectFactory::NewFeature() {
	return new geo3dml::Feature();
}

geo3dml::Point* ObjectFactory::NewPoint() {
	return new Point();
}

geo3dml::MultiPoint* ObjectFactory::NewMultiPoint() {
	return new MultiPoint();
}

geo3dml::LineString* ObjectFactory::NewLineString() {
	return new LineString();
}

geo3dml::TIN* ObjectFactory::NewTIN() {
	return new TIN();
}

geo3dml::CornerPointGrid* ObjectFactory::NewCornerPointGrid() {
	return new CornerPointGrid();
}

geo3dml::CornerPointGrid* ObjectFactory::NewCornerPointGrid(int dimI, int dimJ, int dimK) {
	return new CornerPointGrid(dimI, dimJ, dimK);
}

geo3dml::UniformGrid* ObjectFactory::NewUniformGrid() {
	return new UniformGrid();
}

geo3dml::UniformGrid* ObjectFactory::NewUniformGrid(
	double originX, double originY, double originZ,
	double stepX, double stepY, double stepZ,
	int dimI, int dimJ, int dimK
) {
	return new UniformGrid(originX, originY, originZ, stepX, stepY, stepZ, dimI, dimJ, dimK);
}

geo3dml::Annotation* ObjectFactory::NewAnnotation() {
	return new Annotation();
}

geo3dml::ShapeProperty* ObjectFactory::NewShapeProperty() {
	return new ShapeProperty();
}

geo3dml::Actor* ObjectFactory::NewActor() {
	return new Actor();
}