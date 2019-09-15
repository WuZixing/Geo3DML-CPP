#pragma once

#include <string>
#include <map>

namespace g3dvtk {

	class ColorMap;

	class DiscreteAttributeColorTransfer {
	public:
		DiscreteAttributeColorTransfer();
		virtual ~DiscreteAttributeColorTransfer();

		/// @name Initialize the transfer with all available attributes.
		//@{
		void InsertAttribute(const std::string& value);
		void InsertAttribute(int value);
		//@}
		/// Compile the transfer when it has been told all attributes.
		void Compile();
		/// @name Transfer attribute to a color after the transfer has been compiled.
		//@{
		bool PickUpColor(const std::string& value, unsigned char& r, unsigned char& g, unsigned char& b);
		bool PickUpColor(int value, unsigned char& r, unsigned char& g, unsigned char& b);
		bool PickUpColor(const std::string& value, double& r, double& g, double& b);
		bool PickUpColor(int value, double& r, double& g, double& b);
		void RandomColor(unsigned char& r, unsigned char& g, unsigned char& b);
		void RandomColor(double& r, double& g, double& b);
		//@}

	private:
		std::map<std::string, int> strAttributes_;
		std::map<int, int> intAttributes_;
		ColorMap* colorMap_;
	};
}
