// UTF-8编码
#include <geo3dml/DefaultObjectFactory.h>
#include "ShapeProperty.h"
#include "Point.h"
#include "MultiPoint.h"
#include "LineString.h"
#include "MultiLineString.h"
#include "TIN.h"

using namespace geo3dml;

DefaultObjectFactory::DefaultObjectFactory() {

}

DefaultObjectFactory::~DefaultObjectFactory() {

}

ObjectFactory* DefaultObjectFactory::Clone() {
    return new DefaultObjectFactory();
}

Point* DefaultObjectFactory::NewPoint() {
	return new geometry::Point();
}

MultiPoint* DefaultObjectFactory::NewMultiPoint() {
	return new geometry::MultiPoint();
}

LineString* DefaultObjectFactory::NewLineString() {
	return new geometry::LineString();
}

MultiLineString* DefaultObjectFactory::NewMultiLineString() {
	return new geometry::MultiLineString();
}

TIN* DefaultObjectFactory::NewTIN() {
	return new geometry::TIN();
}

CornerPointGrid* DefaultObjectFactory::NewCornerPointGrid() {
	return nullptr;
}

CornerPointGrid* DefaultObjectFactory::NewCornerPointGrid(int dimI, int dimJ, int dimK) {
	return nullptr;
}

Annotation* DefaultObjectFactory::NewAnnotation() {
	return nullptr;
}

TriangularPrismVolume* DefaultObjectFactory::NewTriangularPrismVolume() {
	return nullptr;
}

RectifiedGrid* DefaultObjectFactory::NewRectifiedGrid(
	const geo3dml::Point3D& origin,
	const geo3dml::Vector3D& vecI, const geo3dml::Vector3D& vecJ, const geo3dml::Vector3D& vecK,
	int highI, int highJ, int highK, int lowI, int lowJ, int lowK) {
	return nullptr;
}
RectifiedGrid* DefaultObjectFactory::NewRectifiedGrid(
	const geo3dml::Point3D& origin,
	double stepI, double stepJ, double stepK,
	int highI, int highJ, int highK, int lowI, int lowJ, int lowK) {
	return nullptr;
}

TetrahedronVolume* DefaultObjectFactory::NewTetrahedronVolume() {
	return nullptr;
}

CuboidVolume* DefaultObjectFactory::NewCuboidVolume() {
	return nullptr;
}

TruncatedRegularGrid* DefaultObjectFactory::NewTruncatedRegularGrid() {
	return nullptr;
}

ShapeProperty* DefaultObjectFactory::NewShapeProperty() {
	return new geometry::ShapeProperty();
}

Actor* DefaultObjectFactory::NewActor() {
	return nullptr;
}
