// UTF-8编码
#include <geo3dml/Material.h>

using namespace geo3dml;

Material::Material() {
	ambientIntensity_ = 0.2;
	shininess_ = 0.2;
	transparency_ = 0;
}

Material::~Material() {

}

void Material::SetAmbientIntensity(double d) {
	ambientIntensity_ = d;
}

double Material::GetAmbientIntensity() const {
	return ambientIntensity_;
}

void Material::SetShininess(double d) {
	shininess_ = d;
}

double Material::GetShininess() const {
	return shininess_;
}

void Material::SetTransparency(double d) {
	transparency_ = d;
}

double Material::GetTransparency() const {
	return transparency_;
}

void Material::SetDiffuseColor(const Color& clr) {
	diffuseColor_ = clr;
}

Color Material::GetDiffuseColor() const {
	return diffuseColor_;
}

void Material::SetEmissiveColor(const Color& clr) {
	emissiveColor_ = clr;
}

Color Material::GetEmissiveColor() const {
	return emissiveColor_;
}

void Material::SetSpecularColor(const Color& clr) {
	specularColor_ = clr;
}

Color Material::GetSpecularColor() const {
	return specularColor_;
}

void Material::SetTexture(const Texture& tex) {
	texture_ = tex;
}

const Texture& Material::GetTexture() const {
	return texture_;
}

