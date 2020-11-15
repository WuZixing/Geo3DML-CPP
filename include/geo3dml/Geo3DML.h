#pragma once

#include <string>

namespace geo3dml {
	/// All Geo3DML objects must be thread safe.
	class Object {
	public:
		static std::string NewID();

	public:
		Object();
		virtual ~Object();

		std::string GetID() const;
		void SetID(const std::string& id);

	private:
		std::string id_;
	};
}
