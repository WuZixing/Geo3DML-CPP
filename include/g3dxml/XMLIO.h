#pragma once

#include <string>

namespace g3dxml {

	class XMLIO {
	public:
		XMLIO();
		virtual ~XMLIO();

		bool IsOK() const;
		std::string Error() const;

	protected:
		void SetStatus(bool isOK, const std::string& message = "");

	private:
		bool isOK_;
		std::string errorMessage_;
	};
}
