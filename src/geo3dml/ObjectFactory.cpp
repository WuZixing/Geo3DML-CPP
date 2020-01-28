#include <geo3dml/ObjectFactory.h>
#include <geo3dml/Utils.h>

using namespace geo3dml;

ObjectFactory::ObjectFactory() {
}

ObjectFactory::~ObjectFactory() {
}

Map* ObjectFactory::NewMap() {
	return new Map();
}

Layer* ObjectFactory::NewLayer() {
	return new Layer();
}


Geometry* ObjectFactory::NewGeometry(const std::string& typeName) {
	if (IsiEqual(typeName, "GeoTIN")) {
		return NewTIN();
	} else if (IsiEqual(typeName, "GeoCornerPointGrid")) {
		return NewCornerPointGrid();
	} else if (IsiEqual(typeName, "GeoUniformGrid")) {
		return NewUniformGrid();
	} else if (IsiEqual(typeName, "LineString")) {
		return NewLineString();
	} else if (IsiEqual(typeName, "Point")) {
		return NewPoint();
	} else {
		return NULL;
	}
}

std::string ObjectFactory::TypeNameOfGeometry(Geometry* shape) {
	TIN* tin = dynamic_cast<TIN*>(shape);
	if (tin != NULL) {
		return "GeoTIN";
	}
	CornerPointGrid* cGrid = dynamic_cast<CornerPointGrid*>(shape);
	if (cGrid != NULL) {
		return "GeoCornerPointGrid";
	}
	UniformGrid* rGrid = dynamic_cast<UniformGrid*>(shape);
	if (rGrid != NULL) {
		return "GeoUniformGrid";
	}
	LineString* line = dynamic_cast<LineString*>(shape);
	if (line != NULL) {
		return "LineString";
	}
	Point* point = dynamic_cast<Point*>(shape);
	if (point != NULL) {
		return "Point";
	}
	return "";
}

PointSymbolizer* ObjectFactory::NewPointSymbolizer() {
	return new PointSymbolizer();
}

LineSymbolizer* ObjectFactory::NewLineSymbolizer() {
	return new LineSymbolizer();
}

SurfaceSymbolizer* ObjectFactory::NewSurfaceSymbolizer() {
	return new SurfaceSymbolizer();
}

FeatureTypeStyle* ObjectFactory::NewFeatureTypeStyle() {
	return new FeatureTypeStyle();
}

GeoDiscreteCoverageSymbolizer* ObjectFactory::NewGeoDiscreteCoverageSymbolizer() {
	return new GeoDiscreteCoverageSymbolizer();
}
