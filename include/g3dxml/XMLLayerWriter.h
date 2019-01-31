#pragma once

#include <g3dxml/XMLIO.h>
#include <iostream>
#include <geo3dml/Layer.h>
#include <geo3dml/FeatureTypeStyle.h>
#include <geo3dml/PointSymbolizer.h>
#include <geo3dml/LineSymbolizer.h>
#include <geo3dml/SurfaceSymbolizer.h>
#include <geo3dml/GeoDiscreteCoverageSymbolizer.h>

namespace g3dxml {

	class XMLLayerWriter : public XMLIO {
	public:
		XMLLayerWriter();
		virtual ~XMLLayerWriter();

		bool Write(geo3dml::Layer* layer, std::ostream& output, SchemaVersion v);

	private:
		void WriteStyle(geo3dml::Geo3DStyle* style, std::ostream& output);
		void WriteFeatureTypeStyle(geo3dml::FeatureTypeStyle* featureStyle, std::ostream& output);
		void WriteStyleRule(geo3dml::StyleRule* rule, std::ostream& output);
		void WriteSymbolizer(geo3dml::Symbolizer* sym, std::ostream& output);
		void WritePointSymbolizer(geo3dml::PointSymbolizer* pointSym, std::ostream& output);
		void WriteLineSymbolizer(geo3dml::LineSymbolizer* lineSym, std::ostream& output);
		void WriteSurfaceSymbolizer(geo3dml::SurfaceSymbolizer* surfaceSym, std::ostream& output);
		void WriteGeoDiscreteCoverageSymbolizer(geo3dml::GeoDiscreteCoverageSymbolizer* coverageSym, std::ostream& output);
		void WriteMaterial(const geo3dml::Material& m, std::ostream& output);
	};
}
