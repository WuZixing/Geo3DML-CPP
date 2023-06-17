// UTF-8编码
#include <geo3dml/Metadata.h>

using namespace geo3dml;

Metadata::Metadata() {
    isDateStampDateTime_ = false;
}

Metadata::~Metadata() {

}

const std::string& Metadata::GetDateStamp(bool& isDateTime) const {
    isDateTime = isDateStampDateTime_;
    return dateStamp_;
}

void Metadata::SetDateStamp(const std::string& s, bool isDateTime) {
    dateStamp_ = s;
    isDateStampDateTime_ = isDateTime;
}

const std::string& Metadata::GetDescription() const {
    return description_;
}

void Metadata::SetDescription(const std::string& s) {
    description_ = s;
}

const std::string& Metadata::GetVersion() const {
    return version_;
}

void Metadata::SetVersion(const std::string& s) {
    version_ = s;
}

const std::string& Metadata::GetToolName() const {
    return toolName_;
}

void Metadata::SetToolName(const std::string& s) {
    toolName_ = s;
}

const std::string& Metadata::GetToolVersion() const {
    return toolVersion_;
}
void Metadata::SetToolVersion(const std::string& s) {
    toolVersion_ = s;
}

const std::string& Metadata::GetCoordRefSysID() const {
    return coordRefSysId_;
}

void Metadata::SetCoordRefSysID(const std::string& crsID) {
    coordRefSysId_ = crsID;
}

const std::string& Metadata::GetCoordRefSysParam() const {
    return coordRefSysParam_;
}

void Metadata::SetCoordRefSysParam(const std::string& crsParam) {
    coordRefSysParam_ = crsParam;
}

const std::string& Metadata::GetVerticalRefSysCategory() const {
    return verticalRefSysCategory_;
}

void Metadata::SetVerticalRefSysCategory(const std::string& vrsCategory) {
    verticalRefSysCategory_ = vrsCategory;
}

const std::string& Metadata::GetVerticalRefSysValue() const {
    return verticalRefSysValue_;
}

void Metadata::SetVerticalRefSysValue(const std::string& vRefSys) {
    verticalRefSysValue_ = vRefSys;
}

const std::string& Metadata::GetResponsibleIndividualName() const {
    return nameOfResponsibleIndividual_;
}

void Metadata::SetResponsibleIndividualName(const std::string& name) {
    nameOfResponsibleIndividual_ = name;
}

const std::string& Metadata::GetResponsibleOrganisationName() const {
    return nameOfResponsibleOrganisation_;
}

void Metadata::SetResponsibleOrganisationName(const std::string& name) {
    nameOfResponsibleOrganisation_ = name;
}

const std::string& Metadata::GetContactPhone() const {
    return contactPhone_;
}

void Metadata::SetContactPhone(const std::string& phone) {
    contactPhone_ = phone;
}

const std::string& Metadata::GetContactAddress() const {
    return contactAddress_;
}

void Metadata::SetContactAddress(const std::string& address) {
    contactAddress_ = address;
}

const std::string& Metadata::GetContactEmail() const {
    return contactEmail_;
}

void Metadata::SetContactEmail(const std::string& email) {
    contactEmail_ = email;
}
