// UTF-8编码
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
		void WriteStyle(geo3dml::Style* style, std::ostream& output, SchemaVersion v);
		void WriteFeatureTypeStyle(geo3dml::FeatureTypeStyle* featureStyle, std::ostream& output, SchemaVersion v);
		void WriteStyleRule(geo3dml::StyleRule* rule, std::ostream& output, SchemaVersion v);
		void WriteSymbolizer(geo3dml::Symbolizer* sym, std::ostream& output, SchemaVersion v);
		void WritePointSymbolizer(geo3dml::PointSymbolizer* pointSym, std::ostream& output, SchemaVersion v);
		void WriteLineSymbolizer(geo3dml::LineSymbolizer* lineSym, std::ostream& output, SchemaVersion v);
		void WriteSurfaceSymbolizer(geo3dml::SurfaceSymbolizer* surfaceSym, std::ostream& output, SchemaVersion v);
		void WriteGeoDiscreteCoverageSymbolizer(geo3dml::GeoDiscreteCoverageSymbolizer* coverageSym, std::ostream& output, SchemaVersion v);
		void WriteMaterial(const geo3dml::PBRMaterial& m, std::ostream& output, SchemaVersion v);
		void WriteTexture(const std::string& texTag, const geo3dml::Texture& tex, std::ostream& output, SchemaVersion v);
	};
}
