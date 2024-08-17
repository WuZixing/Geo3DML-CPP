// UTF-8编码
#include <geo3dml/PBRMaterial.h>

using namespace geo3dml;

PBRMaterial::PBRMaterial() {
	metallic_ = 0.3;
	roughness_ = 0.7;
	indexOfRefraction_ = 0;
}

PBRMaterial::~PBRMaterial() {

}

void PBRMaterial::SetBaseColor(const Color& clr) {
	baseColor_ = clr;
}

const Color& PBRMaterial::GetBaseColor() const {
	return baseColor_;
}

void PBRMaterial::SetEmissiveColor(const Color& clr) {
	emissiveColor_ = clr;
}

const Color& PBRMaterial::GetEmissiveColor() const {
	return emissiveColor_;
}

void PBRMaterial::SetBaseTexture(const Texture& tex) {
	baseTexture_ = tex;
}

const Texture& PBRMaterial::GetBaseTexture() const {
	return baseTexture_;
}

void PBRMaterial::SetNormalTexture(const Texture& tex) {
	normalTexture_ = tex;
}

const Texture& PBRMaterial::GetNormalTexture() const {
	return normalTexture_;
}

void PBRMaterial::SetOcclusionTexture(const Texture& tex) {
	occlusionTexture_ = tex;
}

const Texture& PBRMaterial::GetOcclusionTexture() const {
	return occlusionTexture_;
}

void PBRMaterial::SetMetallic(double metallic) {
	metallic_ = metallic;
}

double PBRMaterial::GetMetallic() const {
	return metallic_;
}

void PBRMaterial::SetRoughness(double roughness) {
	roughness_ = roughness;
}

double PBRMaterial::GetRoughness() const {
	return roughness_;
}

/// 镜面反射颜色。金属材质的高光颜色。
void PBRMaterial::SetSpecularColor(const Color& clr) {
	specularColor_ = clr;
}

const Color& PBRMaterial::GetSpecularColor() const {
	return specularColor_;
}

void PBRMaterial::SetIndexOfRefraction(double refraction) {
	indexOfRefraction_ = refraction;
}

double PBRMaterial::GetIndexOfRefraction() const {
	return indexOfRefraction_;
}
