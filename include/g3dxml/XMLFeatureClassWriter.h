#pragma once

#include <geo3dml/FeatureClass.h>
#include <iostream>
#include <g3dxml/XMLIO.h>

namespace g3dxml {

	class XMLFeatureClassWriter : public XMLIO {
	public:
		XMLFeatureClassWriter();
		virtual ~XMLFeatureClassWriter();

		bool Write(geo3dml::FeatureClass* fc, std::ostream& output, SchemaVersion v);

	private:
		void WriteSchema(geo3dml::FeatureClass* fc, std::ostream& output);
		void WriteFeatures(geo3dml::FeatureClass* fc, std::ostream& output, SchemaVersion v);
		void WriteFeature(geo3dml::Feature* feature, std::ostream& output, SchemaVersion v);
	};
}
