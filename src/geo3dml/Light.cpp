#include <geo3dml/Light.h>

using namespace geo3dml;

Light::Type Light::NameToLightType(const std::string& name) {
	if (_stricmp(name.c_str(), "Head") == 0) {
		return Light_Head;
	} else if (_stricmp(name.c_str(), "Camera") == 0) {
		return Light_Camera;
	} else {
		return Light_Scene;
	}
}

Light::Light() {
	isOn_ = true;
	lightType_ = Light_Scene;
	for (int i = 0; i < 3; ++i) {
		position_[i] = 0;
		focalPosition_[i] = 0;
	}
	position_[2] = 1.0;
	intensity_ = 1.0;
	ambientColor_ = Color(1.0, 1.0, 1.0);
	diffuseColor_ = Color(1.0, 1.0, 1.0);
	specularColor_ = Color(1.0, 1.0, 1.0);
}

Light::~Light() {

}

Light& Light::Switch(bool on) {
	isOn_ = on;
	return *this;
}

bool Light::IsOn() const {
	return isOn_;
}

Light& Light::SetType(Light::Type t) {
	lightType_ = t;
	return *this;
}

Light::Type Light::GetType() const {
	return lightType_;
}

Light& Light::SetPosition(double x, double y, double z) {
	position_[0] = x;
	position_[1] = y;
	position_[2] = z;
	return *this;
}

void Light::GetPosition(double& x, double& y, double& z) {
	x = position_[0];
	y = position_[1];
	z = position_[2];
}

Light& Light::SetFocalPosition(double x, double y, double z) {
	focalPosition_[0] = x;
	focalPosition_[1] = y;
	focalPosition_[2] = z;
	return *this;
}

void Light::GetFocalPosition(double& x, double& y, double& z) {
	x = focalPosition_[0];
	y = focalPosition_[1];
	z = focalPosition_[2];
}

Light& Light::SetIntensity(double i) {
	intensity_ = i;
	return *this;
}

double Light::GetIntensity() const {
	return intensity_;
}

Light& Light::SetAmbientColor(const Color& c) {
	ambientColor_ = c;
	return *this;
}

Color Light::GetAmbientColor() const {
	return ambientColor_;
}

Light& Light::SetDiffuseColor(const Color& c) {
	diffuseColor_ = c;
	return *this;
}

Color Light::GetDiffuseColor() const {
	return diffuseColor_;
}

Light& Light::SetSpecularColor(const Color& c) {
	specularColor_ = c;
	return *this;
}

Color Light::GetSpecularColor() const {
	return specularColor_;
}
