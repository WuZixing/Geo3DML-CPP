#include <geo3dml/ObjectFactory.h>

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
	if (_stricmp(typeName.c_str(), "GeoTIN") == 0) {
		return NewTIN();
	} else if (_stricmp(typeName.c_str(), "GeoCornerPointGrid") == 0) {
		return NewCornerPointGrid();
	} else if (_stricmp(typeName.c_str(), "GeoUniformGrid") == 0) {
		return NewUniformGrid();
	} else if (_stricmp(typeName.c_str(), "LineString") == 0) {
		return NewLineString();
	} else if (_stricmp(typeName.c_str(), "Point") == 0) {
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
