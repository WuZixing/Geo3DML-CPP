// UTF-8编码
#include <geo3dml/FeatureRelation.h>

using namespace geo3dml;

FeatureRelation::RelationType FeatureRelation::NameToFeatureRelationType(const std::string& name) {
    if (name.compare("GeologicalHistory")) {
        return RelationType::GEOLOGICAL_HISTORY;
    } else if (name.compare("ContactRelation")) {
        return RelationType::CONTACT;
    } else if (name.compare("IntrusiveRelation")) {
        return RelationType::INTRUSIVE;
    } else if (name.compare("GeologicalStructure")) {
        return RelationType::GEOLOGICAL_STRUCTURE;
    } else if (name.compare("AggregationRelation")) {
        return RelationType::AGGREGATION;
    } else if (name.compare("BoundaryRelation")) {
        return RelationType::BOUNDARY;
    } else {
        return RelationType::GENERAL;
    }
}

std::string FeatureRelation::FeatureRelationTypeToName(FeatureRelation::RelationType t) {
    switch (t) {
    case RelationType::GENERAL:
        return std::string("GeoFeatureRelation");
    case RelationType::GEOLOGICAL_HISTORY:
        return std::string("GeologicalHistory");
    case RelationType::CONTACT:
        return std::string("ContactRelation");
    case RelationType::INTRUSIVE:
        return std::string("IntrusiveRelation");
    case RelationType::GEOLOGICAL_STRUCTURE:
        return std::string("GeologicalStructure");
    case RelationType::AGGREGATION:
        return std::string("AggregationRelation");
    case RelationType::BOUNDARY:
        return std::string("BoundaryRelation");
    default:
        return std::string("GeoFeatureRelation");
    }
}

FeatureRelation::FeatureRelation(RelationType type) {
    type_ = type;
}

FeatureRelation::~FeatureRelation() {

}

FeatureRelation::RelationType FeatureRelation::GetRelationType() const {
    return type_;
}

FeatureRelation& FeatureRelation::SetName(const std::string& name) {
    name_ = name;
    return *this;
}

const std::string& FeatureRelation::GetName() const {
    return name_;
}

FeatureRelation& FeatureRelation::SetSourceFeatureId(const std::string& featureId) {
    sourceFeatureId_ = featureId;
    return *this;
}

const std::string& FeatureRelation::GetSourceFeatureId() const {
    return sourceFeatureId_;
}

FeatureRelation& FeatureRelation::SetSourceRole(const std::string& role) {
    sourceRole_ = role;
    return *this;
}

const std::string& FeatureRelation::GetSourceRole() const {
    return sourceRole_;
}

void FeatureRelation::AddTargetFeatureId(const std::string& featureId) {
    targetFeatureIds_.push_back(featureId);
}

int FeatureRelation::GetTargetFeatureCount() const {
    return targetFeatureIds_.size();
}

const std::string& FeatureRelation::GetTargetFeatureId(int i) {
    return targetFeatureIds_.at(i);
}

FeatureRelation& FeatureRelation::SetTargetRole(const std::string& role) {
    targetRole_ = role;
    return *this;
}

const std::string& FeatureRelation::GetTargetRole() const {
    return targetRole_;
}
