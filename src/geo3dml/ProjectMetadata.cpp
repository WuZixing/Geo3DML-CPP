// UTF-8编码
#include <geo3dml/ProjectMetadata.h>

using namespace geo3dml;

bool ProjectMetadata::IsEmpty() const {
    return IsProjectInfoEmpty() && AbstractMetadata::IsEmpty();
}

bool ProjectMetadata::IsProjectInfoEmpty() const {
    return projectName_.empty() && projectCode_.empty() && startDate_.empty() && completeDate_.empty() && contractor_.empty();
}

const std::string& ProjectMetadata::GetProjectName() const {
    return projectName_;
}

void ProjectMetadata::SetProjectName(const std::string& name) {
    projectName_ = name;
}

const std::string& ProjectMetadata::GetProjectCode() const {
    return projectCode_;
}

void ProjectMetadata::SetProjectCode(const std::string& code) {
    projectCode_ = code;
}

const std::string& ProjectMetadata::GetStartDate() const {
    return startDate_;
}

void ProjectMetadata::SetStartDate(const std::string& s) {
    startDate_ = s;
}

const std::string& ProjectMetadata::GetCompleteDate() const {
    return completeDate_;
}

void ProjectMetadata::SetCompleteDate(const std::string& s) {
    completeDate_ = s;
}

const std::string& ProjectMetadata::GetContractor() const {
    return contractor_;
}

void ProjectMetadata::SetContractor(const std::string& contractor) {
    contractor_ = contractor;
}
