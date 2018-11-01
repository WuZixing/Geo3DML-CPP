#include <geo3dml/ObjectFactory.h>

using namespace geo3dml;

ObjectFactory::ObjectFactory() {
}

ObjectFactory::~ObjectFactory() {
}

Geometry* ObjectFactory::NewGeometry() {
	return new Geometry();
}

Shape* ObjectFactory::NewShape(const std::string& typeName) {
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

std::string ObjectFactory::TypeNameOfShape(Shape* shape) {
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
