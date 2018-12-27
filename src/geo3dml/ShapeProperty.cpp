#include <geo3dml/ShapeProperty.h>

using namespace geo3dml;

Version::Version() {

}

Version::~Version() {

}

Version& Version::VersionNo(const std::string& v) {
	versionNo_ = v;
	return *this;
}

std::string Version::VersionNo() const {
	return versionNo_;
}

Version& Version::Timestamp(const std::string& t) {
	timestamp_ = t;
	return *this;
}

std::string Version::Timestamp() const {
	return timestamp_;
}

ShapeProperty::SamplingTarget ShapeProperty::NameToSamplingTarget(const std::string& name) {
	if (_stricmp(name.c_str(), "VOXEL") == 0) {
		return Voxel;
	} else if (_stricmp(name.c_str(), "VERTEX") == 0) {
		return Vertex;
	} else if (_stricmp(name.c_str(), "EDGE") == 0) {
		return Edge;
	} else if (_stricmp(name.c_str(), "FACE") == 0) {
		return Face;
	} else {
		return Unknown;
	}
}

std::string ShapeProperty::SamplingTargetToName(ShapeProperty::SamplingTarget t) {
	switch (t) {
	case Voxel:
		return "VOXEL";
	case Vertex:
		return "VERTEX";
	case Edge:
		return "EDGE";
	case Face:
		return "FACE";
	default:
		return "";
	}
}

ShapeProperty::ShapeProperty() {
	samplingTarget_ = Unknown;
}

ShapeProperty::~ShapeProperty() {

}

ShapeProperty& ShapeProperty::Target(const std::string& shapeId, SamplingTarget t) {
	g3d_lock_guard lck(mtx_);
	targetShapeId_ = shapeId;
	samplingTarget_ = t;
	return *this;
}

std::string ShapeProperty::TargetShape() {
	g3d_lock_guard lck(mtx_);
	return targetShapeId_;
}

ShapeProperty::SamplingTarget ShapeProperty::TargetComponent() {
	g3d_lock_guard lck(mtx_);
	return samplingTarget_;
}

ShapeProperty& ShapeProperty::Name(const std::string& name) {
	g3d_lock_guard lck(mtx_);
	name_ = name;
	return *this;
}

std::string ShapeProperty::Name() {
	g3d_lock_guard lck(mtx_);
	return name_;
}

ShapeProperty& ShapeProperty::VersionInfo(const Version& v) {
	g3d_lock_guard lck(mtx_);
	versionInfo_ = v;
	return *this;
}

const Version& ShapeProperty::VersionInfo() {
	g3d_lock_guard lck(mtx_);
	return versionInfo_;
}

bool ShapeProperty::AddField(const Field& f) {
	g3d_lock_guard lck(mtx_);
	std::vector<Field>::const_iterator citor = fields_.cbegin();
	while (citor != fields_.cend()) {
		if (citor->Name() == f.Name()) {
			break;
		}
		++citor;
	}
	if (citor == fields_.cend()) {
		fields_.push_back(f);
		return true;
	} else {
		return false;
	}
}

int ShapeProperty::GetFieldCount() {
	g3d_lock_guard lck(mtx_);
	return (int)fields_.size();
}

const Field& ShapeProperty::GetFieldAt(int i) {
	g3d_lock_guard lck(mtx_);
	return fields_.at(i);
}

Field ShapeProperty::GetField(const std::string& name) {
	g3d_lock_guard lck(mtx_);
	std::vector<Field>::const_iterator citor = fields_.cbegin();
	while (citor != fields_.cend()) {
		if (citor->Name() == name) {
			return *citor;
		}
		++citor;
	}
	return Field();
}

int ShapeProperty::GetFieldIndex(const std::string& name) {
	g3d_lock_guard lck(mtx_);
	std::vector<Field>::const_iterator citor = fields_.cbegin();
	int index = 0;
	while (citor != fields_.cend()) {
		if (citor->Name() == name) {
			return index;
		}
		++citor;
		++index;
	}
	return -1;
}
