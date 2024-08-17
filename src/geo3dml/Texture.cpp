// UTF-8编码
#include <geo3dml/Texture.h>

using namespace geo3dml;

bool GBSymbol::IsEmpty() const {
	return code_.empty();
}

void GBSymbol::Clear() {
	code_.clear();
}

void GBSymbol::SetCode(const std::string& code) {
	code_ = code;
}

const std::string& GBSymbol::GetCode() const {
	return code_;
}

void GBSymbol::SetStrokeColor(const Color& clr) {
	strokeColor_ = clr;
}

const Color& GBSymbol::GetStrokeColor() const {
	return strokeColor_;
}

void GBSymbol::SetFillColor(const Color& clr) {
	fillColor_ = clr;
}

const Color& GBSymbol::GetFillColor() const {
	return fillColor_;
}

Texture::Texture() {
	wrapMode_ = WrapMode::Default;
}

bool Texture::IsValid() const {
	return !IsImageEmpty() || !gbSymbol_.IsEmpty();
}

bool Texture::IsImageEmpty() const {
	return imageURI_.empty();
}

bool Texture::IsGBSymbolEmpty() const {
	return gbSymbol_.IsEmpty();
}

void Texture::SetImageURI(const std::string& uri) {
	imageURI_ = uri;
	gbSymbol_.Clear();
}

const std::string& Texture::GetImageURI() const {
	return imageURI_;
}

void Texture::SetImageMime(const std::string& mime) {
	imageMime_ = mime;
	gbSymbol_.Clear();
}

const std::string& Texture::GetImageMime() const {
	return imageMime_;
}

void Texture::SetGBSymbol(const GBSymbol& symbol) {
	imageURI_.clear();
	imageMime_.clear();
	gbSymbol_ = symbol;
}

const GBSymbol& Texture::GetGBSymbol() const {
	return gbSymbol_;
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
