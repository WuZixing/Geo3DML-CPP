#pragma once

#include <string>

namespace g3dvtk {

	class ColorMap {
	public:
		static ColorMap* NewDefaultMap();
	public:
		ColorMap();
		virtual ~ColorMap();

		/// Name of the color map.
		virtual std::string Name() const = 0;
		/// Number of the color entries in the map.
		virtual int Size() const = 0;
		/// Fetch colors.
		virtual void ColorAt(int i, unsigned char& r, unsigned char& g, unsigned char& b) const = 0;
		virtual void ColorAt(int i, double& r, double& g, double& b) const = 0;
		virtual void RandomColor(unsigned char& r, unsigned char& g, unsigned char& b);
		virtual void RandomColor(double& r, double& g, double& b);
	};
}
