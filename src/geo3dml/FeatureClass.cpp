#include <geo3dml/FeatureClass.h>

using namespace geo3dml;

FeatureClass::FeatureClass() {

}

FeatureClass::~FeatureClass() {
	std::vector<Feature*>::const_iterator citor = features_.cbegin();
	while (citor != features_.cend()) {
		delete *citor;
		citor++;
	}
}

FeatureClass& FeatureClass::SetName(const std::string& name) {
	g3d_lock_guard lck(mtx_);
	name_ = name;
	return *this;
}

std::string FeatureClass::GetName() {
	g3d_lock_guard lck(mtx_);
	return name_;
}

FeatureClass& FeatureClass::AddFeature(Feature* f) {
	g3d_lock_guard lck(mtx_);
	if (f == NULL)
		return *this;
	std::vector<Feature*>::const_iterator citor = features_.cbegin();
	while (citor != features_.cend()) {
		if (*citor == f)
			return *this;
		citor++;
	}
	features_.push_back(f);
	f->SetParentFeatureClass(GetID());
	return *this;
}

int FeatureClass::GetFeatureCount() {
	g3d_lock_guard lck(mtx_);
	if (features_.empty()) {
		Context* ctx = GetContext();
		if (ctx != NULL && !ctx->IsDone()) {
			ctx->LoadMoreData();
		}
	}
	return (int)features_.size();
}

Feature* FeatureClass::GetFeatureAt(int i) {
	g3d_lock_guard lck(mtx_);
	if (features_.empty()) {
		Context* ctx = GetContext();
		if (ctx != NULL && !ctx->IsDone()) {
			ctx->LoadMoreData();
		}
	}
	return features_.at(i);
}

FeatureClass& FeatureClass::SetParentModel(const std::string& id) {
	g3d_lock_guard lck(mtx_);
	parentModelId_ = id;
	return *this;
}

std::string FeatureClass::GetParentModel() {
	g3d_lock_guard lck(mtx_);
	return parentModelId_;
}

FeatureClass& FeatureClass::AddField(const Field& f) {
	g3d_lock_guard lck(mtx_);
	fields_.push_back(f);
	return *this;
}

int FeatureClass::GetFieldCount() {
	g3d_lock_guard lck(mtx_);
	if (fields_.empty()) {
		Context* ctx = GetContext();
		if (ctx != NULL && !ctx->IsDone()) {
			ctx->LoadMoreData();
		}
	}
	return (int)fields_.size();
}

const Field& FeatureClass::GetFieldAt(int i) {
	g3d_lock_guard lck(mtx_);
	if (fields_.empty()) {
		Context* ctx = GetContext();
		if (ctx != NULL && !ctx->IsDone()) {
			ctx->LoadMoreData();
		}
	}
	return fields_.at(i);
}
