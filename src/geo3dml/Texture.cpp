// UTF-8编码
#include <geo3dml/Texture.h>

using namespace geo3dml;

Texture::Texture() {
	wrapMode_ = WrapMode::Default;
}

bool Texture::IsValid() const {
	return !imageURI_.empty();
}

void Texture::SetImageURI(const std::string& uri) {
	imageURI_ = uri;
}

const std::string& Texture::GetImageURI() const {
	return imageURI_;
}

void Texture::SetImageMime(const std::string& mime) {
	imageMime_ = mime;
}

const std::string& Texture::GetImageMime() const {
	return imageMime_;
}

void Texture::SetWrapMode(Texture::WrapMode mode) {
	wrapMode_ = mode;
}

Texture::WrapMode Texture::GetWrapMode() const {
	return wrapMode_;
}

void Texture::SetBorderColor(const Color& clr) {
	borderColor_ = clr;
}

const Color& Texture::GetBorderColor() const {
	return borderColor_;
}
