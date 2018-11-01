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
	context_ = NULL;
}

Object::~Object() {
	if (context_ != NULL) {
		delete context_;
		context_ = NULL;
	}
}

std::string Object::GetID() {
	g3d_lock_guard lck(mtx_);
	return id_;
}

void Object::SetID(const std::string& id) {
	g3d_lock_guard lck(mtx_);
	id_ = id;
}

void Object::SetContext(Context* ctx) {
	g3d_lock_guard lck(mtx_);
	if (context_ != NULL) {
		delete context_;
		context_ = NULL;
	}
	context_ = ctx;
	if (context_ != NULL) {
		context_->BindGeo3DMLObject(this);
	}
}

Context* Object::GetContext() {
	g3d_lock_guard lck(mtx_);
	return context_;
}
