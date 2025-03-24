#include <geo3dml/Geo3DML.h>
#define UUID_IMPLEMENTATION
#include "uuid.h"

using namespace geo3dml;

std::string Object::NewID() {
	uuid id;
	uuid4_generate(&id);
	char strId[37] = {'\0'};
	return uuid_to_string(&id, strId);
}

Object::Object() {

}

Object::~Object() {

}

const std::string& Object::GetID() const {
	return id_;
}

void Object::SetID(const std::string& id) {
	id_ = id;
}
