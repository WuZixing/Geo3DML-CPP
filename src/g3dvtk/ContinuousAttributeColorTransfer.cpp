#include <g3dvtk/ContinuousAttributeColorTransfer.h>
#include <g3dvtk/ColorMap.h>
#include <cmath>

using namespace g3dvtk;

ContinuousAttributeColorTransfer::ContinuousAttributeColorTransfer() {
	minValue_ = 0;
	maxValue_ = 0;
	colorMap_ = ColorMap::NewDefaultMap();
}

ContinuousAttributeColorTransfer::~ContinuousAttributeColorTransfer() {
	delete colorMap_;
}

void ContinuousAttributeColorTransfer::SetAttributeRange(double min, double max) {
	minValue_ = min;
	maxValue_ = max;
}

void ContinuousAttributeColorTransfer::PickUpColor(double value, unsigned char& r, unsigned char& g, unsigned char& b) {
	int index = 0;
	if (value <= minValue_) {
		index = 0;
	} else if (value >= maxValue_) {
		index = colorMap_->Size() - 1;
	} else {
		double t = (value - minValue_) / (maxValue_ - minValue_);
		index = int(std::floor(t * (colorMap_->Size() - 1)));
	}
	colorMap_->ColorAt(index, r, g, b);
}

void ContinuousAttributeColorTransfer::PickUpColor(double value, double& r, double& g, double& b) {
	unsigned char bR = 0, bG = 0, bB = 0;
	PickUpColor(value, bR, bG, bB);
	r = bR / 255.0f;
	g = bG / 255.0f;
	b = bB / 255.0f;
}
