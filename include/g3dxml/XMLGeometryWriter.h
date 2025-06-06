// UTF-8编码
#pragma once

#include <iostream>
#include <geo3dml/TIN.h>
#include <geo3dml/Annotation.h>
#include <geo3dml/LineString.h>
#include <geo3dml/MultiLineString.h>
#include <geo3dml/Point.h>
#include <geo3dml/MultiPoint.h>
#include <geo3dml/CornerPointGrid.h>
#include <geo3dml/TriangularPrismVolume.h>
#include <geo3dml/RectifiedGrid.h>
#include <geo3dml/TetrahedronVolume.h>
#include <geo3dml/CuboidVolume.h>
#include <geo3dml/TruncatedRegularGrid.h>
#include <g3dxml/XMLIO.h>

namespace g3dxml {

	class XMLGeometryWriter : public XMLIO {
	public:
		XMLGeometryWriter();
		virtual ~XMLGeometryWriter();

		bool Write(geo3dml::Geometry* geo, std::ostream& output, SchemaVersion v);

	private:
		void WriteTIN(geo3dml::TIN* tin, std::ostream& output);
		void WriteLineString(geo3dml::LineString* line, std::ostream& output);
		void WriteMultiLineString(geo3dml::MultiLineString* mLine, std::ostream& output);
		void WritePoint(geo3dml::Point* point, std::ostream& output);
		void WriteAnnotation(geo3dml::Annotation* annotation, std::ostream& output);
		void WriteMultiPoint(geo3dml::MultiPoint* mPoint, std::ostream& output);
		void WriteCornerPointGrid(geo3dml::CornerPointGrid* cornerGrid, std::ostream& output);
		void WriteTriangularPrismVolume(geo3dml::TriangularPrismVolume* gtpGrid, std::ostream& output);
		void WriteRectifiedGrid(const geo3dml::RectifiedGrid* grid, std::ostream& output);
		void WriteTetrahedronVolume(const geo3dml::TetrahedronVolume* tetraVolume, std::ostream& output);
		void WriteCuboidVolume(const geo3dml::CuboidVolume* cuboidVolume, std::ostream& output);
		void WriteTruncatedRegularGrid(const geo3dml::TruncatedRegularGrid* trGrid, std::ostream& output);
	};
}
