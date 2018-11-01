#include <geo3dml/Color.h>
#include <cmath>

using namespace geo3dml;

Color::Color() {
	color_ = 0;
}

Color::Color(double r, double g, double b, double a) {
	color_ = 0;
	SetR(r);
	SetG(g);
	SetB(b);
	SetA(a);
}

Color::Color(unsigned char r, unsigned char g, unsigned char b, unsigned char a) {
	color_ = 0;
	SetR(r);
	SetG(g);
	SetB(b);
	SetA(a);
}

Color::~Color() {

}

Color& Color::SetR(double r) {
	unsigned char v = (unsigned char)((long)(std::floor((r * 255))) % 256);
	return SetR(v);
}

Color& Color::SetG(double g) {
	unsigned char v = (unsigned char)((long)(std::floor((g * 255))) % 256);
	return SetG(v);
}

Color& Color::SetB(double b) {
	unsigned char v = (unsigned char)((long)(std::floor((b * 255))) % 256);
	return SetB(v);
}

Color& Color::SetA(double a) {
	unsigned char v = (unsigned char)((long)(std::floor((a * 255))) % 256);
	return SetA(v);
}

Color& Color::SetR(unsigned char r) {
	color_ = (color_ & 0x00FFFFFF) + (r << 24);
	return *this;
}

Color& Color::SetG(unsigned char g) {
	color_ = (color_ & 0xFF00FFFF) + (g << 16);
	return *this;
}

Color& Color::SetB(unsigned char b) {
	color_ = (color_ & 0xFFFF00FF) + (b << 8);
	return *this;
}

Color& Color::SetA(unsigned char a) {
	color_ = (color_ & 0xFFFFFF00) + a;
	return *this;
}

double Color::R() const {
	return r() / 255.0;
}

double Color::G() const {
	return g() / 255.0;
}

double Color::B() const {
	return b() / 255.0;
}

double Color::A() const {
	return a() / 255.0;
}

unsigned char Color::r() const {
	return (color_ & 0xFF000000) >> 24;

}

unsigned char Color::g() const {
	return (unsigned char)((color_ & 0x00FF0000) >> 16);
}

unsigned char Color::b() const {
	return (unsigned char)((color_ & 0x0000FF00) >> 8);
}

unsigned char Color::a() const {
	return (unsigned char)(color_ & 0x000000FF);
}
