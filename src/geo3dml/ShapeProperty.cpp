#include <geo3dml/ShapeProperty.h>
#include <geo3dml/Utils.h>

using namespace geo3dml;

ShapeProperty::Version::Version() {

}

ShapeProperty::Version::~Version() {

}

ShapeProperty::Version& ShapeProperty::Version::VersionNo(const std::string& v) {
	versionNo_ = v;
	return *this;
}

std::string ShapeProperty::Version::VersionNo() const {
	return versionNo_;
}

ShapeProperty::Version& ShapeProperty::Version::Timestamp(const std::string& t) {
	timestamp_ = t;
	return *this;
}

std::string ShapeProperty::Version::Timestamp() const {
	return timestamp_;
}

ShapeProperty::SamplingTarget ShapeProperty::NameToSamplingTarget(const std::string& name) {
	if (IsiEqual(name, "VOXEL")) {
		return Voxel;
	} else if (IsiEqual(name, "VERTEX")) {
		return Vertex;
	} else if (IsiEqual(name, "EDGE")) {
		return Edge;
	} else if (IsiEqual(name, "FACE")) {
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
		return "UNKNOWN";
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

ShapeProperty& ShapeProperty::VersionInfo(const ShapeProperty::Version& v) {
	g3d_lock_guard lck(mtx_);
	versionInfo_ = v;
	return *this;
}

const ShapeProperty::Version& ShapeProperty::VersionInfo() {
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

bool ShapeProperty::CheckOrAddFieldAndFillDefaultValues(const Field& field, int numberOfValues, double defaultDouble, int defaultInt, bool defaultBool, const std::string& defaultText) {
	g3d_lock_guard lck(mtx_);
	const geo3dml::Field& existingField = GetField(field.Name());
	if (existingField.DataType() != geo3dml::Field::Unknown) {
		if (existingField.DataType() == field.DataType()) {
			return true;
		} else {
			return false;
		}
	} else if (!AddField(field)) {
		return false;
	}
	switch (field.DataType()) {
	case geo3dml::Field::Boolean:
		FillBooleanValue(field.Name(), numberOfValues, defaultBool);
		break;
	case geo3dml::Field::Double:
		FillDoubleValue(field.Name(), numberOfValues, defaultDouble);
		break;
	case geo3dml::Field::Integer:
		FillIntValue(field.Name(), numberOfValues, defaultInt);
		break;
	case geo3dml::Field::Text:
		FillTextValue(field.Name(), numberOfValues, defaultText);
		break;
	default:
	        break;
	}
	return true;
}
