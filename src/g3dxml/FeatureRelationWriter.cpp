// UTF-8编码
#include "FeatureRelationWriter.h"
#include <geo3dml/AggregationRelation.h>
#include <geo3dml/BoundaryRelation.h>
#include <geo3dml/ContactRelation.h>
#include <geo3dml/GeologicalHistory.h>
#include <geo3dml/GeologicalStructure.h>

using namespace g3dxml;

FeatureRelationWriter::FeatureRelationWriter() {

}

FeatureRelationWriter::~FeatureRelationWriter() {

}

bool FeatureRelationWriter::Write(geo3dml::FeatureRelation* fr, std::ostream& output) {
    if (fr == nullptr) {
        SetStatus(false, "null FeatureRelation");
        return false;
    }
    std::string rTag = GetRelationTagName(fr);
    if (rTag.empty()) {
        SetStatus(false, "unknown feature relation");
        return false;
    }
    output << "<" << rTag << " gml:id=\"" << fr->GetID() << "\">" << std::endl
        << "<gml:name>" << fr->GetName() << "</gml:name>" << std::endl
        << "<Source>" << std::endl
        << "<Role>" << fr->GetSourceRole() << "</Role>" << std::endl
        << "<Feature xlink:type=\"simple\" xlink:href=\"" << fr->GetSourceFeatureId() << "\" />" << std::endl
        << "</Source>" << std::endl
        << "<Targets>" << std::endl
        << "<Role>" << fr->GetTargetRole() << "</Role>" << std::endl;
    int targetFeatureNumber = fr->GetTargetFeatureCount();
    for (int i = 0; i < targetFeatureNumber; ++i) {
        const std::string& featureId = fr->GetTargetFeatureId(i);
        output << "<Feature xlink:type=\"simple\" xlink:href=\"" << featureId << "\" />" << std::endl;
    }
    output << "</Targets>" << std::endl
        << "</" << rTag << ">" << std::endl;
}

void FeatureRelationWriter::WriteFeature(const std::string& id, std::ostream& output) {

}

std::string FeatureRelationWriter::GetRelationTagName(const geo3dml::FeatureRelation* fr) const {
    const geo3dml::AggregationRelation* aggregation = dynamic_cast<const geo3dml::AggregationRelation*>(fr);
    if (aggregation != nullptr) {
        return std::string("AggregationRelation");
    } else {
        const geo3dml::BoundaryRelation* boundary = dynamic_cast<const geo3dml::BoundaryRelation*>(fr);
        if (boundary != nullptr) {
            return std::string("BoundaryRelation");
        } else {
            const geo3dml::ContactRelation* contact = dynamic_cast<const geo3dml::ContactRelation*>(fr);
            if (contact != nullptr) {
                return std::string("ContactRelation");
            } else {
                const geo3dml::GeologicalHistory* geoHistory = dynamic_cast<const geo3dml::GeologicalHistory*>(fr);
                if (geoHistory != nullptr) {
                    return std::string("GeologicalHistory");
                } else {
                    const geo3dml::GeologicalStructure* geoStructure = dynamic_cast<const geo3dml::GeologicalStructure*>(fr);
                    if (geoStructure != nullptr) {
                        return std::string("GeologicalStructure");
                    }
                }
            }
        }
    }

    return std::string();
}
