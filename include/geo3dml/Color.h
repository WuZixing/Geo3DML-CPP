#pragma once

namespace geo3dml {

	class Color {
	public:
		Color();
		Color(double r, double g, double b, double a = 0.0);
		Color(unsigned char r, unsigned char g, unsigned char b, unsigned char a = 0);
		virtual ~Color();

		Color& SetR(double r);
		Color& SetG(double g);
		Color& SetB(double b);
		Color& SetA(double a);
		Color& SetR(unsigned char r);
		Color& SetG(unsigned char g);
		Color& SetB(unsigned char b);
		Color& SetA(unsigned char a);

		double R() const;
		double G() const;
		double B() const;
		double A() const;
		unsigned char r() const;
		unsigned char g() const;
		unsigned char b() const;
		unsigned char a() const;

	private:
		unsigned long color_;
	};
}
