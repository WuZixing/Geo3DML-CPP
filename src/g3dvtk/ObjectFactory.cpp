#include <g3dvtk/ObjectFactory.h>
#include <g3dvtk/TIN.h>
#include <g3dvtk/CornerPointGrid.h>
#include <g3dvtk/LineString.h>
#include <g3dvtk/ShapeProperty.h>
#include <g3dvtk/Point.h>
#include <g3dvtk/MultiPoint.h>
#include <g3dvtk/Actor.h>
#include <g3dvtk/Annotation.h>
#include <g3dvtk/MultiLineString.h>
#include <g3dvtk/TriangularPrismVolume.h>
#include <g3dvtk/RectifiedGrid.h>
#include <g3dvtk/TetrahedronVolume.h>
#include <g3dvtk/CuboidVolume.h>
#include <g3dvtk/TruncatedRegularGrid.h>

using namespace g3dvtk;

ObjectFactory::ObjectFactory() {

}

ObjectFactory::~ObjectFactory() {

}

ObjectFactory* ObjectFactory::Clone() {
	return new ObjectFactory();
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

geo3dml::MultiLineString* ObjectFactory::NewMultiLineString() {
	return new MultiLineString();
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

geo3dml::Annotation* ObjectFactory::NewAnnotation() {
	return new Annotation();
}

geo3dml::TriangularPrismVolume* ObjectFactory::NewTriangularPrismVolume() {
	return new TriangularPrismVolume();
}

geo3dml::ShapeProperty* ObjectFactory::NewShapeProperty() {
	return new ShapeProperty();
}

geo3dml::Actor* ObjectFactory::NewActor() {
	return new Actor();
}

geo3dml::RectifiedGrid* ObjectFactory::NewRectifiedGrid(
	const geo3dml::Point3D& origin,
	const geo3dml::Vector3D& vecI, const geo3dml::Vector3D& vecJ, const geo3dml::Vector3D& vecK,
	int highI, int highJ, int highK, int lowI, int lowJ, int lowK) {
	return new RectifiedGrid(origin, vecI, vecJ, vecK, highI, highJ, highK, lowI, lowJ, lowK);
}

geo3dml::RectifiedGrid* ObjectFactory::NewRectifiedGrid(
	const geo3dml::Point3D& origin,
	double stepI, double stepJ, double stepK,
	int highI, int highJ, int highK, int lowI, int lowJ, int lowK) {
	return new RectifiedGrid(origin, stepI, stepJ, stepK, highI, highJ, highK, lowI, lowJ, lowK);
}

geo3dml::TetrahedronVolume* ObjectFactory::NewTetrahedronVolume() {
	return new TetrahedronVolume();
}

geo3dml::CuboidVolume* ObjectFactory::NewCuboidVolume() {
	return new CuboidVolume();
}

geo3dml::TruncatedRegularGrid* ObjectFactory::NewTruncatedRegularGrid() {
	return new TruncatedRegularGrid();
}
