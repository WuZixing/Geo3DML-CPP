// UTF-8编码
#pragma once

#include <geo3dml/FeatureRelation.h>
#include <iostream>
#include <g3dxml/XMLIO.h>

namespace g3dxml {

	class XMLFeatureRelationWriter : public XMLIO {
	public:
		XMLFeatureRelationWriter();
		virtual ~XMLFeatureRelationWriter();

		bool Write(geo3dml::FeatureRelation* fr, std::ostream& output);

	private:
		void WriteFeature(const std::string& id, std::ostream& output);

		std::string GetRelationTagName(const geo3dml::FeatureRelation* fr) const;
	};
}
