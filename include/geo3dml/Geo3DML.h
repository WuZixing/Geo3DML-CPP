#pragma once

#include <string>

namespace geo3dml {
	class Object {
	public:
		static std::string NewID();

	public:
		Object();
		virtual ~Object();

		const std::string& GetID() const;
		void SetID(const std::string& id);

	private:
		std::string id_;
	};
}
