#include <g3dvtk/DiscreteAttributeColorTransfer.h>
#include <g3dvtk/ColorMap.h>
#include <cmath>

using namespace g3dvtk;

DiscreteAttributeColorTransfer::DiscreteAttributeColorTransfer() {
	colorMap_ = ColorMap::NewDefaultMap();
}

DiscreteAttributeColorTransfer::~DiscreteAttributeColorTransfer() {
	delete colorMap_;
}

void DiscreteAttributeColorTransfer::InsertAttribute(const std::string& value) {
	strAttributes_[value] = -1;
}

void DiscreteAttributeColorTransfer::InsertAttribute(int value) {
	intAttributes_[value] = -1;
}

void DiscreteAttributeColorTransfer::Compile() {
	// string attributes.
	size_t numberOfAttributes = strAttributes_.size();
	if (numberOfAttributes > 0) {
		std::map<std::string, int>::iterator itor = strAttributes_.begin();
		itor->second = 0;
		if (numberOfAttributes > 1) {
			double step = (colorMap_->Size() - 1) * 1.0 / (numberOfAttributes - 1);
			int i = 1;
			++itor;
			while (itor != strAttributes_.end()) {
				itor->second = int(std::floor(i++ * step));
				++itor;
			}
		}
	}
	// integer attributes.
	numberOfAttributes = intAttributes_.size();
	if (numberOfAttributes > 0) {
		std::map<int, int>::iterator itor = intAttributes_.begin();
		itor->second = 0;
		if (numberOfAttributes > 1) {
			double step = (colorMap_->Size() - 1) * 1.0 / (numberOfAttributes - 1);
			int i = 1;
			++itor;
			while (itor != intAttributes_.end()) {
				itor->second = int(std::floor(i++ * step));
				++itor;
			}
		}
	}
}

bool DiscreteAttributeColorTransfer::PickUpColor(const std::string& value, unsigned char& r, unsigned char& g, unsigned char& b) {
	std::map<std::string, int>::const_iterator citor = strAttributes_.find(value);
	if (citor == strAttributes_.cend()) {
		return false;
	}
	colorMap_->ColorAt(citor->second, r, g, b);
	return true;
}

bool DiscreteAttributeColorTransfer::PickUpColor(int value, unsigned char& r, unsigned char& g, unsigned char& b) {
	std::map<int, int>::const_iterator citor = intAttributes_.find(value);
	if (citor == intAttributes_.cend()) {
		return false;
	}
	colorMap_->ColorAt(citor->second, r, g, b);
	return true;
}

bool DiscreteAttributeColorTransfer::PickUpColor(const std::string& value, double& r, double& g, double& b) {
	std::map<std::string, int>::const_iterator citor = strAttributes_.find(value);
	if (citor == strAttributes_.cend()) {
		return false;
	}
	colorMap_->ColorAt(citor->second, r, g, b);
	return true;
}

bool DiscreteAttributeColorTransfer::PickUpColor(int value, double& r, double& g, double& b) {
	std::map<int, int>::const_iterator citor = intAttributes_.find(value);
	if (citor == intAttributes_.cend()) {
		return false;
	}
	colorMap_->ColorAt(citor->second, r, g, b);
	return true;
}

void DiscreteAttributeColorTransfer::RandomColor(unsigned char& r, unsigned char& g, unsigned char& b) {
	colorMap_->RandomColor(r, g, b);
}

void DiscreteAttributeColorTransfer::RandomColor(double& r, double& g, double& b) {
	colorMap_->RandomColor(r, g, b);
}
