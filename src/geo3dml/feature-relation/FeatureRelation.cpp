// UTF-8编码
#include <geo3dml/FeatureRelation.h>

using namespace geo3dml;

FeatureRelation::FeatureRelation() {

}

FeatureRelation::~FeatureRelation() {

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

const std::string FeatureRelation::GetTargetRole() const {
    return targetRole_;
}
