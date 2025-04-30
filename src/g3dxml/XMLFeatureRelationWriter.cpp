// UTF-8编码
#include "XMLFeatureRelationWriter.h"

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
    output << "<Relation>" << std::endl
        << "<" << rTag << " gml:id=\"" << fr->GetID() << "\">" << std::endl
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
        << "</" << rTag << ">" << std::endl
        << "</Relation>" << std::endl;
    return true;
}

void XMLFeatureRelationWriter::WriteFeature(const std::string& id, std::ostream& output) {
    output << "<Feature xlink:type=\"simple\" xlink:href=\"" << id << "\" />" << std::endl;
}

std::string XMLFeatureRelationWriter::GetRelationTagName(const geo3dml::FeatureRelation* fr) const {
    return geo3dml::FeatureRelation::FeatureRelationTypeToName(fr->GetRelationType());
}
