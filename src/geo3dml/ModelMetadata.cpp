// UTF-8编码
#include <geo3dml/ModelMetadata.h>

using namespace geo3dml;

ModelMetadata::ModelMetadata() {
    isDateStampDateTime_ = false;
}

ModelMetadata::~ModelMetadata() {

}

const std::string& ModelMetadata::GetDateStamp(bool& isDateTime) const {
    isDateTime = isDateStampDateTime_;
    return dateStamp_;
}

void ModelMetadata::SetDateStamp(const std::string& s, bool isDateTime) {
    dateStamp_ = s;
    isDateStampDateTime_ = isDateTime;
}

const std::string& ModelMetadata::GetVersion() const {
    return version_;
}

void ModelMetadata::SetVersion(const std::string& s) {
    version_ = s;
}

const std::string& ModelMetadata::GetToolName() const {
    return toolName_;
}

void ModelMetadata::SetToolName(const std::string& s) {
    toolName_ = s;
}

const std::string& ModelMetadata::GetToolVersion() const {
    return toolVersion_;
}
void ModelMetadata::SetToolVersion(const std::string& s) {
    toolVersion_ = s;
}

const std::string& ModelMetadata::GetTopicCategory() const {
    return topicCategory_;
}

void ModelMetadata::SetTopicCategory(const std::string& topic) {
    topicCategory_ = topic;
}

const std::string& ModelMetadata::GetCoordRefSysID() const {
    return coordRefSysId_;
}

void ModelMetadata::SetCoordRefSysID(const std::string& crsID) {
    coordRefSysId_ = crsID;
}

const std::string& ModelMetadata::GetCoordRefSysParam() const {
    return coordRefSysParam_;
}

void ModelMetadata::SetCoordRefSysParam(const std::string& crsParam) {
    coordRefSysParam_ = crsParam;
}

const std::string& ModelMetadata::GetVerticalRefSysCategory() const {
    return verticalRefSysCategory_;
}

void ModelMetadata::SetVerticalRefSysCategory(const std::string& vrsCategory) {
    verticalRefSysCategory_ = vrsCategory;
}

const std::string& ModelMetadata::GetVerticalRefSysValue() const {
    return verticalRefSysValue_;
}

void ModelMetadata::SetVerticalRefSysValue(const std::string& vRefSys) {
    verticalRefSysValue_ = vRefSys;
}

