// UTF-8编码
#include <geo3dml/Material.h>

using namespace geo3dml;

Material::Material() {

}

Material::~Material() {

}

void Material::SetBaseColor(const Color& clr) {
	baseColor_ = clr;
}

const Color& Material::GetBaseColor() const {
	return baseColor_;
}

void Material::SetEmissiveColor(const Color& clr) {
	emissiveColor_ = clr;
}

const Color& Material::GetEmissiveColor() const {
	return emissiveColor_;
}

void Material::SetBaseTexture(const Texture& tex) {
	baseTexture_ = tex;
}

const Texture& Material::GetBaseTexture() const {
	return baseTexture_;
}

void Material::SetNormalTexture(const Texture& tex) {
	normalTexture_ = tex;
}

const Texture& Material::GetNormalTexture() const {
	return normalTexture_;
}

void Material::SetOcclusionTexture(const Texture& tex) {
	occlusionTexture_ = tex;
}

const Texture& Material::GetOcclusionTexture() const {
	return occlusionTexture_;
}
