// UTF-8编码
#include <geo3dml/DefaultObjectFactory.h>
#include "ShapeProperty.h"
#include "Annotation.h"
#include "CornerPointGrid.h"
#include "CuboidVolume.h"
#include "LineString.h"
#include "MultiPoint.h"
#include "MultiLineString.h"
#include "Point.h"
#include "TIN.h"
#include "TetrahedronVolume.h"
#include "TriangularPrismVolume.h"
#include "TruncatedRegularGrid.h"

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
	return new geometry::CornerPointGrid();
}

CornerPointGrid* DefaultObjectFactory::NewCornerPointGrid(int dimI, int dimJ, int dimK) {
	return new geometry::CornerPointGrid(dimI, dimJ, dimK);
}

Annotation* DefaultObjectFactory::NewAnnotation() {
	return new geometry::Annotation();
}

TriangularPrismVolume* DefaultObjectFactory::NewTriangularPrismVolume() {
	return new geometry::TriangularPrismVolume();
}

RectifiedGrid* DefaultObjectFactory::NewRectifiedGrid(
	const geo3dml::Point3D& origin,
	const geo3dml::Vector3D& vecI, const geo3dml::Vector3D& vecJ, const geo3dml::Vector3D& vecK,
	int highI, int highJ, int highK, int lowI, int lowJ, int lowK) {
	return new geo3dml::RectifiedGrid(origin, vecI, vecJ, vecK, highI, highJ, highK, lowI, lowJ, lowK);
}
RectifiedGrid* DefaultObjectFactory::NewRectifiedGrid(
	const geo3dml::Point3D& origin,
	double stepI, double stepJ, double stepK,
	int highI, int highJ, int highK, int lowI, int lowJ, int lowK) {
	return new geo3dml::RectifiedGrid(origin, stepI, stepJ, stepK, highI, highJ, highK, lowI, lowJ, lowK);
}

TetrahedronVolume* DefaultObjectFactory::NewTetrahedronVolume() {
	return new geometry::TetrahedronVolume();
}

CuboidVolume* DefaultObjectFactory::NewCuboidVolume() {
	return new geometry::CuboidVolume();
}

TruncatedRegularGrid* DefaultObjectFactory::NewTruncatedRegularGrid() {
	return new geometry::TruncatedRegularGrid();
}

ShapeProperty* DefaultObjectFactory::NewShapeProperty() {
	return new geometry::ShapeProperty();
}

Actor* DefaultObjectFactory::NewActor() {
	return nullptr;
}
