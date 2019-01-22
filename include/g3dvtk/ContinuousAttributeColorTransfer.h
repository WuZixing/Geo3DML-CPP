#pragma once

namespace g3dvtk {

	class ColorMap;

	class ContinuousAttributeColorTransfer {
	public:
		ContinuousAttributeColorTransfer();
		virtual ~ContinuousAttributeColorTransfer();

		void SetAttributeRange(double min, double max);
		void PickUpColor(double value, unsigned char& r, unsigned char& g, unsigned char& b);
		void PickUpColor(double value, double& r, double& g, double& b);

	private:
		double minValue_, maxValue_;
		ColorMap* colorMap_;
	};
}
