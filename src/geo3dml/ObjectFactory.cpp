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
	if (IsiEqual(typeName, "TIN")) {
		return NewTIN();
	} else if (IsiEqual(typeName, "CornerPointGrid")) {
		return NewCornerPointGrid();
	} else if (IsiEqual(typeName, "CuboidVolume")) {
		return NewCuboidVolume();
	} else if (IsiEqual(typeName, "TriangularPrismVolume")) {
		return NewTriangularPrismVolume();
	} else if (IsiEqual(typeName, "TetrahedronVolume")) {
		return NewTetrahedronVolume();
	} else if (IsiEqual(typeName, "TruncatedRegularGrid")) {
		return NewTruncatedRegularGrid();
	} else if (IsiEqual(typeName, "LineString")) {
		return NewLineString();
	} else if (IsiEqual(typeName, "MultiLineString")) {
		return NewMultiLineString();
	} else if (IsiEqual(typeName, "Point")) {
		return NewPoint();
	} else if (IsiEqual(typeName, "Annotation")) {
		return NewAnnotation();
	} else if (IsiEqual(typeName, "MultiPoint")) {
		return NewMultiPoint();
	} else {
		return nullptr;
	}
}

std::string ObjectFactory::TypeNameOfGeometry(Geometry* shape) {
	TIN* tin = dynamic_cast<TIN*>(shape);
	if (tin != nullptr) {
		return std::string("TIN");
	}
	CornerPointGrid* cGrid = dynamic_cast<CornerPointGrid*>(shape);
	if (cGrid != nullptr) {
		return std::string("CornerPointGrid");
	}
	CuboidVolume* cuboid = dynamic_cast<CuboidVolume*>(shape);
	if (cuboid!= nullptr) {
		return std::string("CuboidVolume");
	}
	TriangularPrismVolume* gtp = dynamic_cast<TriangularPrismVolume*>(shape);
	if (gtp != nullptr) {
		return std::string("TriangularPrismVolume");
	}
	RectifiedGrid* rGrid = dynamic_cast<RectifiedGrid*>(shape);
	if (rGrid != nullptr) {
		return std::string("RectifiedGrid");
	}
	TetrahedronVolume* tetraGrid = dynamic_cast<TetrahedronVolume*>(shape);
	if (tetraGrid != nullptr) {
		return std::string("TetrahedronVolume");
	}
	TruncatedRegularGrid* trGrid = dynamic_cast<TruncatedRegularGrid*>(shape);
	if (trGrid != nullptr) {
		return std::string("TruncatedRegularGrid");
	}
	LineString* line = dynamic_cast<LineString*>(shape);
	if (line != nullptr) {
		return std::string("LineString");
	}
	MultiLineString* mLine = dynamic_cast<MultiLineString*>(shape);
	if (mLine != nullptr) {
		return std::string("MultiLineString");
	}
	Point* point = dynamic_cast<Point*>(shape);
	if (point != nullptr) {
		return std::string("Point");
	}
	Annotation* anno = dynamic_cast<Annotation*>(shape);
	if (anno != nullptr) {
		return std::string("Annotation");
	}
	MultiPoint* mPoint = dynamic_cast<MultiPoint*>(shape);
	if (mPoint != nullptr) {
		return std::string("MultiPoint");
	}
	return std::string();
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
