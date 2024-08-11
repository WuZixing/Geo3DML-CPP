// UTF-8编码
#include <geo3dml/AbstractMetadata.h>

using namespace geo3dml;

AbstractMetadata::~AbstractMetadata() {

}

const std::string& AbstractMetadata::GetDescription() const {
    return description_;
}

void AbstractMetadata::SetDescription(const std::string& s) {
    description_ = s;
}

const std::string& AbstractMetadata::GetResponsibleIndividualName() const {
    return nameOfResponsibleIndividual_;
}

void AbstractMetadata::SetResponsibleIndividualName(const std::string& name) {
    nameOfResponsibleIndividual_ = name;
}

const std::string& AbstractMetadata::GetResponsibleOrganisationName() const {
    return nameOfResponsibleOrganisation_;
}

void AbstractMetadata::SetResponsibleOrganisationName(const std::string& name) {
    nameOfResponsibleOrganisation_ = name;
}

const std::string& AbstractMetadata::GetContactPhone() const {
    return contactPhone_;
}

void AbstractMetadata::SetContactPhone(const std::string& phone) {
    contactPhone_ = phone;
}

const std::string& AbstractMetadata::GetContactAddress() const {
    return contactAddress_;
}

void AbstractMetadata::SetContactAddress(const std::string& address) {
    contactAddress_ = address;
}

const std::string& AbstractMetadata::GetContactEmail() const {
    return contactEmail_;
}

void AbstractMetadata::SetContactEmail(const std::string& email) {
    contactEmail_ = email;
}

bool AbstractMetadata::IsContactEmpty() const {
    return nameOfResponsibleIndividual_.empty() && nameOfResponsibleOrganisation_.empty() && contactPhone_.empty() && contactAddress_.empty() && contactEmail_.empty();
}

bool AbstractMetadata::IsEmpty() const {
    return description_.empty() && IsContactEmpty();
}
