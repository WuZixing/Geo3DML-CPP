#include <g3dxml/XMLIO.h>

using namespace g3dxml;

std::string g3dxml::SchemaVersionToString(SchemaVersion v) {
	switch (v) {
	case Schema_1_0:
		return "1.0";
	case Schema_1_x:
		return "1.x";
	default:
		return "";
	}
}

SchemaVersion g3dxml::StringToSchemaVersion(const std::string& s) {
	if (_stricmp(s.c_str(), "1.0") == 0) {
		return Schema_1_0;
	} else if (_stricmp(s.c_str(), "1.x") == 0) {
		return Schema_1_x;
	} else {
		return Schema_Unknown;
	}
}

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
