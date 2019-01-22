#pragma once

#include "ColorMap.h"

namespace g3dvtk {

	/// Color map of Plasma from <a href="http://www.kennethmoreland.com/color-advice/">Color Map Advice for Scientific Visualization</a>.
	class ColorMapPlasma : public ColorMap {
	public:
		ColorMapPlasma();
		virtual ~ColorMapPlasma();

		/// @name Methods inherited from #ColorMap .
		//@{
		virtual std::string Name() const;
		virtual int Size() const;
		virtual void ColorAt(int i, unsigned char& r, unsigned char& g, unsigned char& b) const;
		virtual void ColorAt(int i, double& r, double& g, double& b) const;
		//@}

	};
}
