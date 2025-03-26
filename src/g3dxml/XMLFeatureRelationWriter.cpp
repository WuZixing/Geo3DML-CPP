// UTF-8编码
#include "XMLFeatureRelationWriter.h"
#include <geo3dml/AggregationRelation.h>
#include <geo3dml/BoundaryRelation.h>
#include <geo3dml/ContactRelation.h>
#include <geo3dml/GeologicalHistory.h>
#include <geo3dml/GeologicalStructure.h>

using namespace g3dxml;

XMLFeatureRelationWriter::XMLFeatureRelationWriter() {

}

XMLFeatureRelationWriter::~XMLFeatureRelationWriter() {

}

bool XMLFeatureRelationWriter::Write(geo3dml::FeatureRelation* fr, std::ostream& output) {
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
        << "<Source>" << std::endl;
    const std::string& sourceRole = fr->GetSourceRole();
    if (!sourceRole.empty()) {
        output << "<Role>" << sourceRole << "</Role>" << std::endl;
    }
    WriteFeature(fr->GetSourceFeatureId(), output);
    output << "</Source>" << std::endl
        << "<Targets>" << std::endl;
    const std::string& targetRole = fr->GetTargetRole();
    if (!targetRole.empty()) {
        output << "<Role>" << targetRole << "</Role>" << std::endl;
    }
    int targetFeatureNumber = fr->GetTargetFeatureCount();
    for (int i = 0; i < targetFeatureNumber; ++i) {
        const std::string& featureId = fr->GetTargetFeatureId(i);
        WriteFeature(featureId, output);
    }
    output << "</Targets>" << std::endl
        << "</" << rTag << ">" << std::endl;
    return true;
}

void XMLFeatureRelationWriter::WriteFeature(const std::string& id, std::ostream& output) {
    output << "<Feature xlink:type=\"simple\" xlink:href=\"" << id << "\" />" << std::endl;
}

std::string XMLFeatureRelationWriter::GetRelationTagName(const geo3dml::FeatureRelation* fr) const {
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
