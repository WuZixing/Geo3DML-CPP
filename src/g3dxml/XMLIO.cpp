#include <g3dxml/XMLIO.h>

using namespace g3dxml;

XMLIO::XMLIO() {
	isOK_ = true;
}

XMLIO::~XMLIO() {

}

bool XMLIO::IsOK() const {
	return isOK_;
}

std::string XMLIO::Error() const {
	return errorMessage_;
}

void XMLIO::SetStatus(bool isOK, const std::string& message) {
	isOK_ = isOK;
	errorMessage_ = message;
}
