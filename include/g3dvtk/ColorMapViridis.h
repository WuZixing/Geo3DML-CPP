#pragma once

#include "ColorMap.h"

namespace g3dvtk {

	/// Color map of Viridis from <a href="http://www.kennethmoreland.com/color-advice/">Color Map Advice for Scientific Visualization</a>.
	class ColorMapViridis : public ColorMap {
	public:
		ColorMapViridis();
		virtual ~ColorMapViridis();

		/// @name Methods inherited from #ColorMap .
		//@{
		virtual std::string Name() const;
		virtual int Size() const;
		virtual void ColorAt(int i, unsigned char& r, unsigned char& g, unsigned char& b) const;
		virtual void ColorAt(int i, double& r, double& g, double& b) const;
		//@}
	};
}
