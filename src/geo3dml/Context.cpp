#include <geo3dml/Context.h>
#include <geo3dml/ObjectFactory.h>

using namespace geo3dml;

Context::Context(ObjectFactory* g3dFactory) {
	g3dObject_ = NULL;
	isDone_ = true;
	g3dFactory_ = g3dFactory->Clone();
}

Context::~Context() {
	if (g3dFactory_ != NULL) {
		delete g3dFactory_;
		g3dFactory_ = NULL;
	}
}

void Context::BindGeo3DMLObject(Object* g3dObject) {
	g3dcpp_context_lock_guard lck(mtx_);
	g3dObject_ = g3dObject;
}

Object* Context::GetGeo3DMLObject() {
	g3dcpp_context_lock_guard lck(mtx_);
	return g3dObject_;
}

void Context::LoadMoreData() {

}

void Context::SetDone(bool isDone) {
	g3dcpp_context_lock_guard lck(mtx_);
	isDone_ = isDone;
}

bool Context::IsDone() {
	g3dcpp_context_lock_guard lck(mtx_);
	return isDone_;
}

bool Context::IsOK() {
	g3dcpp_context_lock_guard lck(mtx_);
	return isOK_;
}

std::string Context::Error() {
	g3dcpp_context_lock_guard lck(mtx_);
	return errorMessage_;
}

void Context::SetStatus(bool isOK, const std::string& message) {
	g3dcpp_context_lock_guard lck(mtx_);
	isOK_ = isOK;
	errorMessage_ = message;
}

ObjectFactory* Context::GetObjectFactory() {
	g3dcpp_context_lock_guard lck(mtx_);
	return g3dFactory_;
}
