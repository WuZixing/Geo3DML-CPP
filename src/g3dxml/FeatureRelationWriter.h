// UTF-8编码
#pragma once

#include <geo3dml/FeatureRelation.h>
#include <iostream>
#include <g3dxml/XMLIO.h>

namespace g3dxml {

	class FeatureRelationWriter : public XMLIO {
	public:
		FeatureRelationWriter();
		virtual ~FeatureRelationWriter();

		bool Write(geo3dml::FeatureRelation* fr, std::ostream& output);

	private:
		void WriteFeature(const std::string& id, std::ostream& output);

		std::string GetRelationTagName(const geo3dml::FeatureRelation* fr) const;
	};
}
