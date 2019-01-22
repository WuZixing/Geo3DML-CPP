#include <g3dvtk/ColorMap.h>
#include <g3dvtk/ColorMapCoolToWarm.h>
#include <g3dvtk/ColorMapPlasma.h>
#include <g3dvtk/ColorMapViridis.h>

using namespace g3dvtk;

ColorMap* ColorMap::NewDefaultMap() {
	return new ColorMapCoolToWarm();
}

ColorMap::ColorMap() {

}

ColorMap::~ColorMap() {

}

void ColorMap::RandomColor(unsigned char& r, unsigned char& g, unsigned char& b) {
	const int round = Size();
	ColorAt(rand() % round, r, g, b);
}

void ColorMap::RandomColor(double& r, double& g, double& b) {
	const int round = Size();
	ColorAt(rand() % round, r, g, b);
}
